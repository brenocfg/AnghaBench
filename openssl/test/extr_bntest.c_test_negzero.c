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
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ge_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 

__attribute__((used)) static int test_negzero(void)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL, *d = NULL;
    BIGNUM *numerator = NULL, *denominator = NULL;
    int consttime, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(c = BN_new())
            || !TEST_ptr(d = BN_new()))
        goto err;

    /* Test that BN_mul never gives negative zero. */
    if (!TEST_true(BN_set_word(a, 1)))
        goto err;
    BN_set_negative(a, 1);
    BN_zero(b);
    if (!TEST_true(BN_mul(c, a, b, ctx)))
        goto err;
    if (!TEST_BN_eq_zero(c)
            || !TEST_BN_ge_zero(c))
        goto err;

    for (consttime = 0; consttime < 2; consttime++) {
        if (!TEST_ptr(numerator = BN_new())
                || !TEST_ptr(denominator = BN_new()))
            goto err;
        if (consttime) {
            BN_set_flags(numerator, BN_FLG_CONSTTIME);
            BN_set_flags(denominator, BN_FLG_CONSTTIME);
        }
        /* Test that BN_div never gives negative zero in the quotient. */
        if (!TEST_true(BN_set_word(numerator, 1))
                || !TEST_true(BN_set_word(denominator, 2)))
            goto err;
        BN_set_negative(numerator, 1);
        if (!TEST_true(BN_div(a, b, numerator, denominator, ctx))
                || !TEST_BN_eq_zero(a)
                || !TEST_BN_ge_zero(a))
            goto err;

        /* Test that BN_div never gives negative zero in the remainder. */
        if (!TEST_true(BN_set_word(denominator, 1))
                || !TEST_true(BN_div(a, b, numerator, denominator, ctx))
                || !TEST_BN_eq_zero(b)
                || !TEST_BN_ge_zero(b))
            goto err;
        BN_free(numerator);
        BN_free(denominator);
        numerator = denominator = NULL;
    }

    /* Test that BN_set_negative will not produce a negative zero. */
    BN_zero(a);
    BN_set_negative(a, 1);
    if (BN_is_negative(a))
        goto err;
    st = 1;

 err:
    BN_free(a);
    BN_free(b);
    BN_free(c);
    BN_free(d);
    BN_free(numerator);
    BN_free(denominator);
    return st;
}