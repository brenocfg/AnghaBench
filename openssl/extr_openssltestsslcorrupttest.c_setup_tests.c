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
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  privkey ; 
 int setup_cipher_list () ; 
 int /*<<< orphan*/  test_get_argument (int) ; 
 int /*<<< orphan*/  test_ssl_corrupt ; 

int setup_tests(void)
{
    int n;

    if (!TEST_ptr(cert = test_get_argument(0))
            || !TEST_ptr(privkey = test_get_argument(1)))
        return 0;

    n = setup_cipher_list();
    if (n > 0)
        ADD_ALL_TESTS(test_ssl_corrupt, n);
    return 1;
}