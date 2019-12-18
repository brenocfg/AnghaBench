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
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cert1 ; 
 int /*<<< orphan*/  cert2 ; 
 int /*<<< orphan*/  ciphers ; 
 int /*<<< orphan*/  privkey1 ; 
 int /*<<< orphan*/  privkey2 ; 
 int /*<<< orphan*/  test_get_argument (int) ; 
 int /*<<< orphan*/  test_tls13 ; 

int setup_tests(void)
{
    if (!TEST_ptr(cert1 = test_get_argument(0))
            || !TEST_ptr(privkey1 = test_get_argument(1))
            || !TEST_ptr(cert2 = test_get_argument(2))
            || !TEST_ptr(privkey2 = test_get_argument(3)))
        return 0;

    ADD_ALL_TESTS(test_tls13, OSSL_NELEM(ciphers));
    return 1;
}