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
 int /*<<< orphan*/  BN_CTX_new () ; 
 scalar_t__ OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  composites ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  test_bn_small_factors ; 
 int /*<<< orphan*/  test_is_composite_enhanced ; 
 int /*<<< orphan*/  test_is_prime_enhanced ; 

int setup_tests(void)
{
    if (!TEST_ptr(ctx = BN_CTX_new()))
        return 0;

    ADD_TEST(test_is_prime_enhanced);
    ADD_ALL_TESTS(test_is_composite_enhanced, (int)OSSL_NELEM(composites));
    ADD_TEST(test_bn_small_factors);

    return 1;
}