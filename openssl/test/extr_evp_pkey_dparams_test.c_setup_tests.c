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
 int /*<<< orphan*/  TEST_note (char*) ; 
 int /*<<< orphan*/  params_bio_test ; 
 int /*<<< orphan*/  pkey_params ; 

int setup_tests(void)
{
#if defined(OPENSSL_NO_DH) && defined(OPENSSL_NO_DSA) && defined(OPENSSL_NO_EC)
    TEST_note("No DH/DSA/EC support");
#else
    ADD_ALL_TESTS(params_bio_test, OSSL_NELEM(pkey_params));
#endif
    return 1;
}