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
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_consttime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont_word (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_expmodzero(void)
{
    BIGNUM *a = NULL, *r = NULL, *zero = NULL;
    int st = 0;

    if (!TEST_ptr(zero = BN_new())
            || !TEST_ptr(a = BN_new())
            || !TEST_ptr(r = BN_new()))
        goto err;
    BN_zero(zero);

    if (!TEST_true(BN_mod_exp(r, a, zero, BN_value_one(), NULL))
            || !TEST_BN_eq_zero(r)
            || !TEST_true(BN_mod_exp_mont(r, a, zero, BN_value_one(),
                                          NULL, NULL))
            || !TEST_BN_eq_zero(r)
            || !TEST_true(BN_mod_exp_mont_consttime(r, a, zero,
                                                    BN_value_one(),
                                                    NULL, NULL))
            || !TEST_BN_eq_zero(r)
            || !TEST_true(BN_mod_exp_mont_word(r, 42, zero,
                                               BN_value_one(), NULL, NULL))
            || !TEST_BN_eq_zero(r))
        goto err;

    st = 1;
 err:
    BN_free(zero);
    BN_free(a);
    BN_free(r);
    return st;
}