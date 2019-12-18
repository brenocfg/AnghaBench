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

/* Variables and functions */
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_int32 ; 
 int /*<<< orphan*/  test_int64 ; 
 int /*<<< orphan*/  test_long_32bit ; 
 int /*<<< orphan*/  test_long_64bit ; 
 int /*<<< orphan*/  test_uint32 ; 
 int /*<<< orphan*/  test_uint64 ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_DEPRECATED_3_0
    ADD_TEST(test_long_32bit);
    ADD_TEST(test_long_64bit);
#endif
    ADD_TEST(test_int32);
    ADD_TEST(test_uint32);
    ADD_TEST(test_int64);
    ADD_TEST(test_uint64);
    return 1;
}