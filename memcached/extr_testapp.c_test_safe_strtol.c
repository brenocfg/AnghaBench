#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int safe_strtol (char*,int*) ; 

__attribute__((used)) static enum test_return test_safe_strtol(void) {
    int32_t val;
    assert(safe_strtol("123", &val));
    assert(val == 123);
    assert(safe_strtol("+123", &val));
    assert(val == 123);
    assert(safe_strtol("-123", &val));
    assert(val == -123);
    assert(!safe_strtol("", &val));  // empty
    assert(!safe_strtol("123BOGUS", &val));  // non-numeric
    assert(!safe_strtol("92837498237498237498029383", &val)); // out of range
    assert(!safe_strtol(" issue221", &val));  // non-numeric

    // extremes:
    /* This actually works on 64-bit ubuntu
       assert(!safe_strtol("2147483648", &val)); // (expt 2.0 31.0)
    */
    assert(safe_strtol("2147483647", &val)); // (- (expt 2.0 31) 1)
    assert(val == 2147483647L);
    /* This actually works on 64-bit ubuntu
       assert(!safe_strtol("-2147483649", &val)); // (- (expt -2.0 31) 1)
    */

    // We'll allow space to terminate the string.  And leading space.
    assert(safe_strtol(" 123 foo", &val));
    assert(val == 123);
    return TEST_PASS;
}