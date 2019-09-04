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
 int /*<<< orphan*/ * ENGINE_by_id (char*) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/  test_afalg_aes_cbc ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_ENGINE
    if ((e = ENGINE_by_id("afalg")) == NULL) {
        /* Probably a platform env issue, not a test failure. */
        TEST_info("Can't load AFALG engine");
    } else {
# ifndef OPENSSL_NO_AFALGENG
        ADD_ALL_TESTS(test_afalg_aes_cbc, 3);
# endif
    }
#endif

    return 1;
}