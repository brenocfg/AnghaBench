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
 int /*<<< orphan*/  BN_GF2m_arr2poly (int const*,int /*<<< orphan*/  const*) ; 
 int BN_GF2m_mod_div (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod_div_arr(BIGNUM *r, const BIGNUM *yy, const BIGNUM *xx,
                        const int p[], BN_CTX *ctx)
{
    BIGNUM *field;
    int ret = 0;

    bn_check_top(yy);
    bn_check_top(xx);

    BN_CTX_start(ctx);
    if ((field = BN_CTX_get(ctx)) == NULL)
        goto err;
    if (!BN_GF2m_arr2poly(p, field))
        goto err;

    ret = BN_GF2m_mod_div(r, yy, xx, field, ctx);
    bn_check_top(r);

 err:
    BN_CTX_end(ctx);
    return ret;
}