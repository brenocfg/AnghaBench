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
 int /*<<< orphan*/  test_sanity_enum_size ; 
 int /*<<< orphan*/  test_sanity_memcmp ; 
 int /*<<< orphan*/  test_sanity_null_zero ; 
 int /*<<< orphan*/  test_sanity_range ; 
 int /*<<< orphan*/  test_sanity_sign ; 
 int /*<<< orphan*/  test_sanity_twos_complement ; 
 int /*<<< orphan*/  test_sanity_unsigned_conversion ; 

int setup_tests(void)
{
    ADD_TEST(test_sanity_null_zero);
    ADD_TEST(test_sanity_enum_size);
    ADD_TEST(test_sanity_twos_complement);
    ADD_TEST(test_sanity_sign);
    ADD_TEST(test_sanity_unsigned_conversion);
    ADD_TEST(test_sanity_range);
    ADD_TEST(test_sanity_memcmp);
    return 1;
}