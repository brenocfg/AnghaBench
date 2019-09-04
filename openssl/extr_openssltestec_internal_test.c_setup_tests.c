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
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int crv_len ; 
 int /*<<< orphan*/ * curves ; 
 int /*<<< orphan*/  field_tests_default ; 
 int /*<<< orphan*/  field_tests_ec2_simple ; 
 int /*<<< orphan*/  field_tests_ecp_mont ; 
 int /*<<< orphan*/  field_tests_ecp_simple ; 

int setup_tests(void)
{
    crv_len = EC_get_builtin_curves(NULL, 0);
    if (!TEST_ptr(curves = OPENSSL_malloc(sizeof(*curves) * crv_len))
        || !TEST_true(EC_get_builtin_curves(curves, crv_len)))
        return 0;

    ADD_TEST(field_tests_ecp_simple);
    ADD_TEST(field_tests_ecp_mont);
#ifndef OPENSSL_NO_EC2M
    ADD_TEST(field_tests_ec2_simple);
#endif
    ADD_ALL_TESTS(field_tests_default, crv_len);
    return 1;
}