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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_F_BN_EXP ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_get_flags (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_bit_set (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_sqr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_exp(BIGNUM *r, const BIGNUM *a, const BIGNUM *p, BN_CTX *ctx)
{
    int i, bits, ret = 0;
    BIGNUM *v, *rr;

    if (BN_get_flags(p, BN_FLG_CONSTTIME) != 0
            || BN_get_flags(a, BN_FLG_CONSTTIME) != 0) {
        /* BN_FLG_CONSTTIME only supported by BN_mod_exp_mont() */
        BNerr(BN_F_BN_EXP, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }

    BN_CTX_start(ctx);
    rr = ((r == a) || (r == p)) ? BN_CTX_get(ctx) : r;
    v = BN_CTX_get(ctx);
    if (rr == NULL || v == NULL)
        goto err;

    if (BN_copy(v, a) == NULL)
        goto err;
    bits = BN_num_bits(p);

    if (BN_is_odd(p)) {
        if (BN_copy(rr, a) == NULL)
            goto err;
    } else {
        if (!BN_one(rr))
            goto err;
    }

    for (i = 1; i < bits; i++) {
        if (!BN_sqr(v, v, ctx))
            goto err;
        if (BN_is_bit_set(p, i)) {
            if (!BN_mul(rr, rr, v, ctx))
                goto err;
        }
    }
    if (r != rr && BN_copy(r, rr) == NULL)
        goto err;

    ret = 1;
 err:
    BN_CTX_end(ctx);
    bn_check_top(r);
    return ret;
}