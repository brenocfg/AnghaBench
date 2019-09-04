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
 int /*<<< orphan*/  RC2key ; 
 int /*<<< orphan*/  test_rc2 ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_RC2
    ADD_ALL_TESTS(test_rc2, OSSL_NELEM(RC2key));
#endif
    return 1;
}