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
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cast_test_iterations ; 
 int /*<<< orphan*/  cast_test_vector ; 
 int /*<<< orphan*/  k_len ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_CAST
    ADD_ALL_TESTS(cast_test_vector, OSSL_NELEM(k_len));
    ADD_TEST(cast_test_iterations);
#endif
    return 1;
}