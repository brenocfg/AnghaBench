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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int EC_get_builtin_curves (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  cardinality_test ; 
 int /*<<< orphan*/  char2_curve_test ; 
 int /*<<< orphan*/  char2_curve_tests ; 
 int /*<<< orphan*/  char2_field_tests ; 
 int /*<<< orphan*/  check_ec_key_field_public_range_test ; 
 int /*<<< orphan*/  check_named_curve_from_ecparameters ; 
 int /*<<< orphan*/  check_named_curve_lookup_test ; 
 int /*<<< orphan*/  check_named_curve_test ; 
 int /*<<< orphan*/  cofactor_range_test ; 
 int crv_len ; 
 int /*<<< orphan*/ * curves ; 
 int /*<<< orphan*/  ec_point_hex2point_test ; 
 int /*<<< orphan*/  group_field_test ; 
 int /*<<< orphan*/  internal_curve_test ; 
 int /*<<< orphan*/  internal_curve_test_method ; 
 int /*<<< orphan*/  nistp_single_test ; 
 int /*<<< orphan*/  nistp_tests_params ; 
 int /*<<< orphan*/  parameter_test ; 
 int /*<<< orphan*/  prime_field_tests ; 
 int /*<<< orphan*/  underflow_test ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_EC
    crv_len = EC_get_builtin_curves(NULL, 0);
    if (!TEST_ptr(curves = OPENSSL_malloc(sizeof(*curves) * crv_len))
        || !TEST_true(EC_get_builtin_curves(curves, crv_len)))
        return 0;

    ADD_TEST(parameter_test);
    ADD_TEST(cofactor_range_test);
    ADD_ALL_TESTS(cardinality_test, crv_len);
    ADD_TEST(prime_field_tests);
# ifndef OPENSSL_NO_EC2M
    ADD_TEST(char2_field_tests);
    ADD_ALL_TESTS(char2_curve_test, OSSL_NELEM(char2_curve_tests));
# endif
# ifndef OPENSSL_NO_EC_NISTP_64_GCC_128
    ADD_ALL_TESTS(nistp_single_test, OSSL_NELEM(nistp_tests_params));
    ADD_TEST(underflow_test);
# endif
    ADD_ALL_TESTS(internal_curve_test, crv_len);
    ADD_ALL_TESTS(internal_curve_test_method, crv_len);
    ADD_TEST(group_field_test);
    ADD_ALL_TESTS(check_named_curve_test, crv_len);
    ADD_ALL_TESTS(check_named_curve_lookup_test, crv_len);
    ADD_ALL_TESTS(check_ec_key_field_public_range_test, crv_len);
    ADD_ALL_TESTS(check_named_curve_from_ecparameters, crv_len);
    ADD_ALL_TESTS(ec_point_hex2point_test, crv_len);
#endif /* OPENSSL_NO_EC */
    return 1;
}