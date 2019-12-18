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
 int /*<<< orphan*/  BN_GF2m_mod_inv (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod_div(BIGNUM *r, const BIGNUM *y, const BIGNUM *x,
                    const BIGNUM *p, BN_CTX *ctx)
{
    BIGNUM *xinv = NULL;
    int ret = 0;

    bn_check_top(y);
    bn_check_top(x);
    bn_check_top(p);

    BN_CTX_start(ctx);
    xinv = BN_CTX_get(ctx);
    if (xinv == NULL)
        goto err;

    if (!BN_GF2m_mod_inv(xinv, x, p, ctx))
        goto err;
    if (!BN_GF2m_mod_mul(r, y, xinv, p, ctx))
        goto err;
    bn_check_top(r);
    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}