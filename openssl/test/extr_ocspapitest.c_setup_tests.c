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
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  certstr ; 
 int /*<<< orphan*/  privkeystr ; 
 int /*<<< orphan*/  test_access_description ; 
 int /*<<< orphan*/  test_get_argument (int) ; 
 int /*<<< orphan*/  test_ocsp_url_svcloc_new ; 
 int /*<<< orphan*/  test_resp_signer ; 

int setup_tests(void)
{
    if (!TEST_ptr(certstr = test_get_argument(0))
        || !TEST_ptr(privkeystr = test_get_argument(1)))
        return 0;
#ifndef OPENSSL_NO_OCSP
    ADD_TEST(test_resp_signer);
    ADD_ALL_TESTS(test_access_description, 3);
    ADD_TEST(test_ocsp_url_svcloc_new);
#endif
    return 1;
}