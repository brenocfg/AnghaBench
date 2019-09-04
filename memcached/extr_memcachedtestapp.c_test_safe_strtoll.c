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
typedef  int int64_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int safe_strtoll (char*,int*) ; 

__attribute__((used)) static enum test_return test_safe_strtoll(void) {
    int64_t val;
    assert(safe_strtoll("123", &val));
    assert(val == 123);
    assert(safe_strtoll("+123", &val));
    assert(val == 123);
    assert(safe_strtoll("-123", &val));
    assert(val == -123);
    assert(!safe_strtoll("", &val));  // empty
    assert(!safe_strtoll("123BOGUS", &val));  // non-numeric
    assert(!safe_strtoll("92837498237498237498029383", &val)); // out of range
    assert(!safe_strtoll(" issue221", &val));  // non-numeric

    // extremes:
    assert(!safe_strtoll("18446744073709551615", &val)); // 2**64 - 1
    assert(safe_strtoll("9223372036854775807", &val)); // 2**63 - 1
    assert(val == 9223372036854775807LL);
    /*
      assert(safe_strtoll("-9223372036854775808", &val)); // -2**63
      assert(val == -9223372036854775808LL);
    */
    assert(!safe_strtoll("-9223372036854775809", &val)); // -2**63 - 1

    // We'll allow space to terminate the string.  And leading space.
    assert(safe_strtoll(" 123 foo", &val));
    assert(val == 123);
    return TEST_PASS;
}