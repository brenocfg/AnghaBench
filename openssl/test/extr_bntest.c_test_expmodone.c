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
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_consttime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_word (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_recp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_simple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_expmodone(void)
{
    int ret = 0, i;
    BIGNUM *r = BN_new();
    BIGNUM *a = BN_new();
    BIGNUM *p = BN_new();
    BIGNUM *m = BN_new();

    if (!TEST_ptr(r)
            || !TEST_ptr(a)
            || !TEST_ptr(p)
            || !TEST_ptr(p)
            || !TEST_ptr(m)
            || !TEST_true(BN_set_word(a, 1))
            || !TEST_true(BN_set_word(p, 0))
            || !TEST_true(BN_set_word(m, 1)))
        goto err;

    /* Calculate r = 1 ^ 0 mod 1, and check the result is always 0 */
    for (i = 0; i < 2; i++) {
        if (!TEST_true(BN_mod_exp(r, a, p, m, NULL))
                || !TEST_BN_eq_zero(r)
                || !TEST_true(BN_mod_exp_mont(r, a, p, m, NULL, NULL))
                || !TEST_BN_eq_zero(r)
                || !TEST_true(BN_mod_exp_mont_consttime(r, a, p, m, NULL, NULL))
                || !TEST_BN_eq_zero(r)
                || !TEST_true(BN_mod_exp_mont_word(r, 1, p, m, NULL, NULL))
                || !TEST_BN_eq_zero(r)
                || !TEST_true(BN_mod_exp_simple(r, a, p, m, NULL))
                || !TEST_BN_eq_zero(r)
                || !TEST_true(BN_mod_exp_recp(r, a, p, m, NULL))
                || !TEST_BN_eq_zero(r))
            goto err;
        /* Repeat for r = 1 ^ 0 mod -1 */
        if (i == 0)
            BN_set_negative(m, 1);
    }

    ret = 1;
 err:
    BN_free(r);
    BN_free(a);
    BN_free(p);
    BN_free(m);
    return ret;
}