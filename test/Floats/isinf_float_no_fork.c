// RUN: %llvmgcc %s -emit-llvm -O0 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t1.bc > %t-output.txt 2>&1
// RUN: FileCheck -input-file=%t-output.txt %s

// FIXME: KLEE needs to be fixed to make this test pass
// XFAIL: *
#include "klee/klee.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
  float x;
  klee_make_symbolic(&x, sizeof(float), "x");
  klee_assume(isinf(x));
  assert(klee_is_infinite_float(x));
}
// CHECK-NOT: invalid klee_assume call (provably false)
// CHECK: KLEE: done: completed paths = 1