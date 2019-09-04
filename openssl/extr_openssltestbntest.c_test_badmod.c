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
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_consttime (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 

__attribute__((used)) static int test_badmod(void)
{
    BIGNUM *a = NULL, *b = NULL, *zero = NULL;
    BN_MONT_CTX *mont = NULL;
    int st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(zero = BN_new())
            || !TEST_ptr(mont = BN_MONT_CTX_new()))
        goto err;
    BN_zero(zero);

    if (!TEST_false(BN_div(a, b, BN_value_one(), zero, ctx)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_mod_mul(a, BN_value_one(), BN_value_one(), zero, ctx)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_mod_exp(a, BN_value_one(), BN_value_one(), zero, ctx)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_mod_exp_mont(a, BN_value_one(), BN_value_one(),
                                    zero, ctx, NULL)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_mod_exp_mont_consttime(a, BN_value_one(), BN_value_one(),
                                              zero, ctx, NULL)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_MONT_CTX_set(mont, zero, ctx)))
        goto err;
    ERR_clear_error();

    /* Some operations also may not be used with an even modulus. */
    if (!TEST_true(BN_set_word(b, 16)))
        goto err;

    if (!TEST_false(BN_MONT_CTX_set(mont, b, ctx)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_mod_exp_mont(a, BN_value_one(), BN_value_one(),
                                    b, ctx, NULL)))
        goto err;
    ERR_clear_error();

    if (!TEST_false(BN_mod_exp_mont_consttime(a, BN_value_one(), BN_value_one(),
                                              b, ctx, NULL)))
        goto err;
    ERR_clear_error();

    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(zero);
    BN_MONT_CTX_free(mont);
    return st;
}