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
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int NUM0 ; 
 scalar_t__ TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_false (int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_neg () ; 

__attribute__((used)) static int test_gf2m_add(void)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL;
    int i, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(c = BN_new()))
        goto err;

    for (i = 0; i < NUM0; i++) {
        if (!(TEST_true(BN_rand(a, 512, 0, 0))
                && TEST_ptr(BN_copy(b, BN_value_one()))))
            goto err;
        BN_set_negative(a, rand_neg());
        BN_set_negative(b, rand_neg());
        if (!(TEST_true(BN_GF2m_add(c, a, b))
                /* Test that two added values have the correct parity. */
                && TEST_false((BN_is_odd(a) && BN_is_odd(c))
                        || (!BN_is_odd(a) && !BN_is_odd(c)))))
            goto err;
        if (!(TEST_true(BN_GF2m_add(c, c, c))
                /* Test that c + c = 0. */
                && TEST_BN_eq_zero(c)))
            goto err;
    }
    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(c);
    return st;
}