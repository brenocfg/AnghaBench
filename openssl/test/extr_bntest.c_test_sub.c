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
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_bntest_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NUM0 ; 
 int NUM1 ; 
 scalar_t__ TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_int_ne (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_neg () ; 

__attribute__((used)) static int test_sub(void)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL;
    int i, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(c = BN_new()))
        goto err;

    for (i = 0; i < NUM0 + NUM1; i++) {
        if (i < NUM1) {
            if (!(TEST_true(BN_bntest_rand(a, 512, 0, 0)))
                    && TEST_ptr(BN_copy(b, a))
                    && TEST_int_ne(BN_set_bit(a, i), 0)
                    && TEST_true(BN_add_word(b, i)))
                goto err;
        } else {
            if (!TEST_true(BN_bntest_rand(b, 400 + i - NUM1, 0, 0)))
                goto err;
            BN_set_negative(a, rand_neg());
            BN_set_negative(b, rand_neg());
        }
        if (!(TEST_true(BN_sub(c, a, b))
                && TEST_true(BN_add(c, c, b))
                && TEST_true(BN_sub(c, c, a))
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