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
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_X931_derive_prime_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int BN_X931_generate_prime_ex(BIGNUM *p, BIGNUM *p1, BIGNUM *p2,
                              BIGNUM *Xp1, BIGNUM *Xp2,
                              const BIGNUM *Xp,
                              const BIGNUM *e, BN_CTX *ctx, BN_GENCB *cb)
{
    int ret = 0;

    BN_CTX_start(ctx);
    if (Xp1 == NULL)
        Xp1 = BN_CTX_get(ctx);
    if (Xp2 == NULL)
        Xp2 = BN_CTX_get(ctx);
    if (Xp1 == NULL || Xp2 == NULL)
        goto error;

    if (!BN_priv_rand_ex(Xp1, 101, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY, ctx))
        goto error;
    if (!BN_priv_rand_ex(Xp2, 101, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY, ctx))
        goto error;
    if (!BN_X931_derive_prime_ex(p, p1, p2, Xp, Xp1, Xp2, e, ctx, cb))
        goto error;

    ret = 1;

 error:
    BN_CTX_end(ctx);

    return ret;

}