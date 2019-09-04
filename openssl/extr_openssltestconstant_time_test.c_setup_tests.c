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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signed_test_values ; 
 int /*<<< orphan*/  test_32values ; 
 int /*<<< orphan*/  test_64values ; 
 int /*<<< orphan*/  test_8values ; 
 int /*<<< orphan*/  test_binops ; 
 int /*<<< orphan*/  test_binops_8 ; 
 int /*<<< orphan*/  test_binops_s ; 
 int /*<<< orphan*/  test_is_zero ; 
 int /*<<< orphan*/  test_is_zero_32 ; 
 int /*<<< orphan*/  test_is_zero_8 ; 
 int /*<<< orphan*/  test_is_zero_s ; 
 int /*<<< orphan*/  test_signed ; 
 int /*<<< orphan*/  test_sizeofs ; 
 int /*<<< orphan*/  test_values ; 
 int /*<<< orphan*/  test_values_32 ; 
 int /*<<< orphan*/  test_values_64 ; 
 int /*<<< orphan*/  test_values_8 ; 
 int /*<<< orphan*/  test_values_s ; 

int setup_tests(void)
{
    ADD_TEST(test_sizeofs);
    ADD_ALL_TESTS(test_is_zero, OSSL_NELEM(test_values));
    ADD_ALL_TESTS(test_is_zero_8, OSSL_NELEM(test_values_8));
    ADD_ALL_TESTS(test_is_zero_32, OSSL_NELEM(test_values_32));
    ADD_ALL_TESTS(test_is_zero_s, OSSL_NELEM(test_values_s));
    ADD_ALL_TESTS(test_binops, OSSL_NELEM(test_values));
    ADD_ALL_TESTS(test_binops_8, OSSL_NELEM(test_values_8));
    ADD_ALL_TESTS(test_binops_s, OSSL_NELEM(test_values_s));
    ADD_ALL_TESTS(test_signed, OSSL_NELEM(signed_test_values));
    ADD_ALL_TESTS(test_8values, OSSL_NELEM(test_values_8));
    ADD_ALL_TESTS(test_32values, OSSL_NELEM(test_values_32));
    ADD_ALL_TESTS(test_64values, OSSL_NELEM(test_values_64));
    return 1;
}