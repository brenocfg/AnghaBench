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
 int /*<<< orphan*/  BN_GF2m_mod_inv_vartime (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ANY ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_priv_rand_ex (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int BN_GF2m_mod_inv(BIGNUM *r, const BIGNUM *a, const BIGNUM *p, BN_CTX *ctx)
{
    BIGNUM *b = NULL;
    int ret = 0;

    BN_CTX_start(ctx);
    if ((b = BN_CTX_get(ctx)) == NULL)
        goto err;

    /* generate blinding value */
    do {
        if (!BN_priv_rand_ex(b, BN_num_bits(p) - 1,
                             BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY, ctx))
            goto err;
    } while (BN_is_zero(b));

    /* r := a * b */
    if (!BN_GF2m_mod_mul(r, a, b, p, ctx))
        goto err;

    /* r := 1/(a * b) */
    if (!BN_GF2m_mod_inv_vartime(r, r, p, ctx))
        goto err;

    /* r := b/(a * b) = 1/a */
    if (!BN_GF2m_mod_mul(r, r, b, p, ctx))
        goto err;

    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}