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
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_f ; 
 int /*<<< orphan*/  req_f ; 
 int /*<<< orphan*/  roots_f ; 
 int /*<<< orphan*/  test_alt_chains_cert_forgery ; 
 int /*<<< orphan*/  test_get_argument (int) ; 
 int /*<<< orphan*/  test_req_sm2_id ; 
 int /*<<< orphan*/  test_sm2_id ; 
 int /*<<< orphan*/  test_store_ctx ; 
 int /*<<< orphan*/  untrusted_f ; 

int setup_tests(void)
{
    if (!TEST_ptr(roots_f = test_get_argument(0))
            || !TEST_ptr(untrusted_f = test_get_argument(1))
            || !TEST_ptr(bad_f = test_get_argument(2))
            || !TEST_ptr(req_f = test_get_argument(3)))
        return 0;

    ADD_TEST(test_alt_chains_cert_forgery);
    ADD_TEST(test_store_ctx);
#ifndef OPENSSL_NO_SM2
    ADD_TEST(test_sm2_id);
    ADD_TEST(test_req_sm2_id);
#endif
    return 1;
}