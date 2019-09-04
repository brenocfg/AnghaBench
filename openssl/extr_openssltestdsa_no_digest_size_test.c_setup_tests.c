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
 int /*<<< orphan*/  dsa_exact_size_test ; 
 int /*<<< orphan*/  dsa_large_digest_test ; 
 int /*<<< orphan*/  dsa_small_digest_test ; 
 int /*<<< orphan*/  genkeys () ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_DSA
    if (!genkeys())
        return 0;

    ADD_TEST(dsa_exact_size_test);
    ADD_TEST(dsa_small_digest_test);
    ADD_TEST(dsa_large_digest_test);
#endif
    return 1;
}