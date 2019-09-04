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
typedef  int BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_consttime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_word (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_recp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_simple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_print_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_is_zero_mod_one (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_mod_exp_zero(void)
{
    BIGNUM *a = NULL, *p = NULL, *m = NULL;
    BIGNUM *r = NULL;
    BN_ULONG one_word = 1;
    BN_CTX *ctx = BN_CTX_new();
    int ret = 1, failed = 0;

    if (!TEST_ptr(m = BN_new())
        || !TEST_ptr(a = BN_new())
        || !TEST_ptr(p = BN_new())
        || !TEST_ptr(r = BN_new()))
        goto err;

    BN_one(m);
    BN_one(a);
    BN_zero(p);

    if (!TEST_true(BN_rand(a, 1024, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY)))
        goto err;

    if (!TEST_true(BN_mod_exp(r, a, p, m, ctx)))
        goto err;

    if (!TEST_true(a_is_zero_mod_one("BN_mod_exp", r, a)))
        failed = 1;

    if (!TEST_true(BN_mod_exp_recp(r, a, p, m, ctx)))
        goto err;

    if (!TEST_true(a_is_zero_mod_one("BN_mod_exp_recp", r, a)))
        failed = 1;

    if (!TEST_true(BN_mod_exp_simple(r, a, p, m, ctx)))
        goto err;

    if (!TEST_true(a_is_zero_mod_one("BN_mod_exp_simple", r, a)))
        failed = 1;

    if (!TEST_true(BN_mod_exp_mont(r, a, p, m, ctx, NULL)))
        goto err;

    if (!TEST_true(a_is_zero_mod_one("BN_mod_exp_mont", r, a)))
        failed = 1;

    if (!TEST_true(BN_mod_exp_mont_consttime(r, a, p, m, ctx, NULL)))
        goto err;

    if (!TEST_true(a_is_zero_mod_one("BN_mod_exp_mont_consttime", r, a)))
        failed = 1;

    /*
     * A different codepath exists for single word multiplication
     * in non-constant-time only.
     */
    if (!TEST_true(BN_mod_exp_mont_word(r, one_word, p, m, ctx, NULL)))
        goto err;

    if (!TEST_BN_eq_zero(r)) {
        TEST_error("BN_mod_exp_mont_word failed: "
                   "1 ** 0 mod 1 = r (should be 0)");
        BN_print_var(r);
        goto err;
    }

    ret = !failed;
 err:
    BN_free(r);
    BN_free(a);
    BN_free(p);
    BN_free(m);
    BN_CTX_free(ctx);

    return ret;
}