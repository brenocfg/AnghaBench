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
typedef  int uint64_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int safe_strtoull (char*,int*) ; 

__attribute__((used)) static enum test_return test_safe_strtoull(void) {
    uint64_t val;
    assert(safe_strtoull("123", &val));
    assert(val == 123);
    assert(safe_strtoull("+123", &val));
    assert(val == 123);
    assert(!safe_strtoull("", &val));  // empty
    assert(!safe_strtoull("123BOGUS", &val));  // non-numeric
    assert(!safe_strtoull("92837498237498237498029383", &val)); // out of range
    assert(!safe_strtoull(" issue221", &val));  // non-numeric

    // extremes:
    assert(safe_strtoull("18446744073709551615", &val)); // 2**64 - 1
    assert(val == 18446744073709551615ULL);
    assert(!safe_strtoull("18446744073709551616", &val)); // 2**64
    assert(!safe_strtoull("-1", &val));  // negative
    return TEST_PASS;
}