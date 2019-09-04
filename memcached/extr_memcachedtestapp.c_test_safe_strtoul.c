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
typedef  int uint32_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int TEST_PASS ; 
 int /*<<< orphan*/  assert (int) ; 
 int safe_strtoul (char*,int*) ; 

__attribute__((used)) static enum test_return test_safe_strtoul(void) {
    uint32_t val;
    assert(safe_strtoul("123", &val));
    assert(val == 123);
    assert(safe_strtoul("+123", &val));
    assert(val == 123);
    assert(!safe_strtoul("", &val));  // empty
    assert(!safe_strtoul("123BOGUS", &val));  // non-numeric
    assert(!safe_strtoul(" issue221", &val));  // non-numeric
    /* Not sure what it does, but this works with ICC :/
       assert(!safe_strtoul("92837498237498237498029383", &val)); // out of range
    */

    // extremes:
    assert(safe_strtoul("4294967295", &val)); // 2**32 - 1
    assert(val == 4294967295L);
    /* This actually works on 64-bit ubuntu
       assert(!safe_strtoul("4294967296", &val)); // 2**32
    */
    assert(!safe_strtoul("-1", &val));  // negative
    return TEST_PASS;
}