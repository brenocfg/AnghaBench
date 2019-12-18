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
 int /*<<< orphan*/  NCONF_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCONF_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_configurations ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  test_bad_configuration ; 
 int /*<<< orphan*/  test_empty_configuration ; 
 int /*<<< orphan*/  test_get_argument (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_good_configuration ; 

int setup_tests(void)
{
    if (!TEST_ptr(conf = NCONF_new(NULL)))
        return 0;
    /* argument should point to test/ssl_test_ctx_test.conf */
    if (!TEST_int_gt(NCONF_load(conf, test_get_argument(0), NULL), 0))
        return 0;

    ADD_TEST(test_empty_configuration);
    ADD_TEST(test_good_configuration);
    ADD_ALL_TESTS(test_bad_configuration, OSSL_NELEM(bad_configurations));
    return 1;
}