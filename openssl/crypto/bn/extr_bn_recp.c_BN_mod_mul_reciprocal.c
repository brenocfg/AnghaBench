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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int BN_div_recp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 

int BN_mod_mul_reciprocal(BIGNUM *r, const BIGNUM *x, const BIGNUM *y,
                          BN_RECP_CTX *recp, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *a;
    const BIGNUM *ca;

    BN_CTX_start(ctx);
    if ((a = BN_CTX_get(ctx)) == NULL)
        goto err;
    if (y != NULL) {
        if (x == y) {
            if (!BN_sqr(a, x, ctx))
                goto err;
        } else {
            if (!BN_mul(a, x, y, ctx))
                goto err;
        }
        ca = a;
    } else
        ca = x;                 /* Just do the mod */

    ret = BN_div_recp(NULL, r, ca, recp, ctx);
 err:
    BN_CTX_end(ctx);
    bn_check_top(r);
    return ret;
}