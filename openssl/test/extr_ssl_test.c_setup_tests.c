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
 int /*<<< orphan*/  NCONF_get_number_e (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,long*) ; 
 int /*<<< orphan*/  NCONF_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCONF_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_ne (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf ; 
 int /*<<< orphan*/  test_get_argument (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_handshake ; 

int setup_tests(void)
{
    long num_tests;

    if (!TEST_ptr(conf = NCONF_new(NULL))
            /* argv[1] should point to the test conf file */
            || !TEST_int_gt(NCONF_load(conf, test_get_argument(0), NULL), 0)
            || !TEST_int_ne(NCONF_get_number_e(conf, NULL, "num_tests",
                                               &num_tests), 0))
        return 0;

    ADD_ALL_TESTS(test_handshake, (int)num_tests);
    return 1;
}