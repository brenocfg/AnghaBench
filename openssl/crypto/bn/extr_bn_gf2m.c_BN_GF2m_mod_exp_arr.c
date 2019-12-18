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
 int /*<<< orphan*/  BN_GF2m_mod_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*) ; 
 int /*<<< orphan*/  BN_GF2m_mod_mul_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_sqr_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_abs_is_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_bit_set (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int BN_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod_exp_arr(BIGNUM *r, const BIGNUM *a, const BIGNUM *b,
                        const int p[], BN_CTX *ctx)
{
    int ret = 0, i, n;
    BIGNUM *u;

    bn_check_top(a);
    bn_check_top(b);

    if (BN_is_zero(b))
        return BN_one(r);

    if (BN_abs_is_word(b, 1))
        return (BN_copy(r, a) != NULL);

    BN_CTX_start(ctx);
    if ((u = BN_CTX_get(ctx)) == NULL)
        goto err;

    if (!BN_GF2m_mod_arr(u, a, p))
        goto err;

    n = BN_num_bits(b) - 1;
    for (i = n - 1; i >= 0; i--) {
        if (!BN_GF2m_mod_sqr_arr(u, u, p, ctx))
            goto err;
        if (BN_is_bit_set(b, i)) {
            if (!BN_GF2m_mod_mul_arr(u, u, a, p, ctx))
                goto err;
        }
    }
    if (!BN_copy(r, u))
        goto err;
    bn_check_top(r);
    ret = 1;
 err:
    BN_CTX_end(ctx);
    return ret;
}