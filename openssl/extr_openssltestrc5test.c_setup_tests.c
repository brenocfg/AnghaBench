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
 int /*<<< orphan*/  RC5_CBC_NUM ; 
 int /*<<< orphan*/  RC5key ; 
 int /*<<< orphan*/  test_rc5_cbc ; 
 int /*<<< orphan*/  test_rc5_ecb ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_RC5
    ADD_ALL_TESTS(test_rc5_ecb, OSSL_NELEM(RC5key));
    ADD_ALL_TESTS(test_rc5_cbc, RC5_CBC_NUM);
#endif
    return 1;
}