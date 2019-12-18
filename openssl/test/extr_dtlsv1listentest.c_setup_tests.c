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
 scalar_t__ OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls_listen_test ; 
 int /*<<< orphan*/  testpackets ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_SOCK
    ADD_ALL_TESTS(dtls_listen_test, (int)OSSL_NELEM(testpackets));
#endif
    return 1;
}