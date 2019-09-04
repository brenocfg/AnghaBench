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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_PRIMETEST_PROBABLY_PRIME ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_miller_rabin_is_prime (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * composites ; 
 int /*<<< orphan*/  ctx ; 

__attribute__((used)) static int test_is_composite_enhanced(int id)
{
    int ret;
    int status = 0;
    BIGNUM *bn = NULL;

    ret = TEST_ptr(bn = BN_new())
          /* negative tests for different composite numbers */
          && TEST_true(BN_set_word(bn, composites[id]))
          && TEST_true(bn_miller_rabin_is_prime(bn, 10, ctx, NULL, 1, &status))
          && TEST_int_ne(status, BN_PRIMETEST_PROBABLY_PRIME);

    BN_free(bn);
    return ret;
}