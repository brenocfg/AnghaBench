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
typedef  int /*<<< orphan*/  BN_RECP_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_RECP_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_RECP_CTX_new () ; 
 int /*<<< orphan*/  BN_RECP_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_bntest_rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div_recp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NUM0 ; 
 int NUM1 ; 
 scalar_t__ TEST_BN_eq_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  rand_neg () ; 

__attribute__((used)) static int test_div_recip(void)
{
    BIGNUM *a = NULL, *b = NULL, *c = NULL, *d = NULL, *e = NULL;
    BN_RECP_CTX *recp = NULL;
    int st = 0, i;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b = BN_new())
            || !TEST_ptr(c = BN_new())
            || !TEST_ptr(d = BN_new())
            || !TEST_ptr(e = BN_new())
            || !TEST_ptr(recp = BN_RECP_CTX_new()))
        goto err;

    for (i = 0; i < NUM0 + NUM1; i++) {
        if (i < NUM1) {
            if (!(TEST_true(BN_bntest_rand(a, 400, 0, 0))
                    && TEST_ptr(BN_copy(b, a))
                    && TEST_true(BN_lshift(a, a, i))
                    && TEST_true(BN_add_word(a, i))))
                goto err;
        } else {
            if (!(TEST_true(BN_bntest_rand(b, 50 + 3 * (i - NUM1), 0, 0))))
                goto err;
        }
        BN_set_negative(a, rand_neg());
        BN_set_negative(b, rand_neg());
        if (!(TEST_true(BN_RECP_CTX_set(recp, b, ctx))
                && TEST_true(BN_div_recp(d, c, a, recp, ctx))
                && TEST_true(BN_mul(e, d, b, ctx))
                && TEST_true(BN_add(d, e, c))
                && TEST_true(BN_sub(d, d, a))
                && TEST_BN_eq_zero(d)))
            goto err;
    }
    st = 1;
 err:
    BN_free(a);
    BN_free(b);
    BN_free(c);
    BN_free(d);
    BN_free(e);
    BN_RECP_CTX_free(recp);
    return st;
}