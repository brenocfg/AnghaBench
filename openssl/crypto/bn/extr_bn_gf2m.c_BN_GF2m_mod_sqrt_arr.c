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
 int BN_GF2m_mod_exp_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod_sqrt_arr(BIGNUM *r, const BIGNUM *a, const int p[],
                         BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *u;

    bn_check_top(a);

    if (p[0] == 0) {
        /* reduction mod 1 => return 0 */
        BN_zero(r);
        return 1;
    }

    BN_CTX_start(ctx);
    if ((u = BN_CTX_get(ctx)) == NULL)
        goto err;

    if (!BN_set_bit(u, p[0] - 1))
        goto err;
    ret = BN_GF2m_mod_exp_arr(r, a, u, p, ctx);
    bn_check_top(r);

 err:
    BN_CTX_end(ctx);
    return ret;
}