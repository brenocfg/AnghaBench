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
 int /*<<< orphan*/  raw_values ; 
 int /*<<< orphan*/  test_param_bignum ; 
 int /*<<< orphan*/  test_param_construct ; 
 int /*<<< orphan*/  test_param_int ; 
 int /*<<< orphan*/  test_param_int32 ; 
 int /*<<< orphan*/  test_param_int64 ; 
 int /*<<< orphan*/  test_param_long ; 
 int /*<<< orphan*/  test_param_real ; 
 int /*<<< orphan*/  test_param_size_t ; 
 int /*<<< orphan*/  test_param_uint ; 
 int /*<<< orphan*/  test_param_uint32 ; 
 int /*<<< orphan*/  test_param_uint64 ; 
 int /*<<< orphan*/  test_param_ulong ; 

int setup_tests(void)
{
    ADD_ALL_TESTS(test_param_int, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_long, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_uint, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_ulong, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_int32, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_uint32, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_size_t, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_int64, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_uint64, OSSL_NELEM(raw_values));
    ADD_ALL_TESTS(test_param_bignum, OSSL_NELEM(raw_values));
    ADD_TEST(test_param_real);
    ADD_TEST(test_param_construct);
    return 1;
}