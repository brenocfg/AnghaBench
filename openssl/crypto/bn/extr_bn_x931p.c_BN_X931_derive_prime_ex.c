#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
struct TYPE_37__ {scalar_t__ neg; } ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 TYPE_1__ const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_add (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int BN_check_prime (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_gcd (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_odd (TYPE_1__ const*) ; 
 scalar_t__ BN_is_one (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_mod_inverse (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_sub (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_sub_word (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  bn_x931_derive_pi (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int BN_X931_derive_prime_ex(BIGNUM *p, BIGNUM *p1, BIGNUM *p2,
                            const BIGNUM *Xp, const BIGNUM *Xp1,
                            const BIGNUM *Xp2, const BIGNUM *e, BN_CTX *ctx,
                            BN_GENCB *cb)
{
    int ret = 0;

    BIGNUM *t, *p1p2, *pm1;

    /* Only even e supported */
    if (!BN_is_odd(e))
        return 0;

    BN_CTX_start(ctx);
    if (p1 == NULL)
        p1 = BN_CTX_get(ctx);

    if (p2 == NULL)
        p2 = BN_CTX_get(ctx);

    t = BN_CTX_get(ctx);

    p1p2 = BN_CTX_get(ctx);

    pm1 = BN_CTX_get(ctx);

    if (pm1 == NULL)
        goto err;

    if (!bn_x931_derive_pi(p1, Xp1, ctx, cb))
        goto err;

    if (!bn_x931_derive_pi(p2, Xp2, ctx, cb))
        goto err;

    if (!BN_mul(p1p2, p1, p2, ctx))
        goto err;

    /* First set p to value of Rp */

    if (!BN_mod_inverse(p, p2, p1, ctx))
        goto err;

    if (!BN_mul(p, p, p2, ctx))
        goto err;

    if (!BN_mod_inverse(t, p1, p2, ctx))
        goto err;

    if (!BN_mul(t, t, p1, ctx))
        goto err;

    if (!BN_sub(p, p, t))
        goto err;

    if (p->neg && !BN_add(p, p, p1p2))
        goto err;

    /* p now equals Rp */

    if (!BN_mod_sub(p, p, Xp, p1p2, ctx))
        goto err;

    if (!BN_add(p, p, Xp))
        goto err;

    /* p now equals Yp0 */

    for (;;) {
        int i = 1;
        BN_GENCB_call(cb, 0, i++);
        if (!BN_copy(pm1, p))
            goto err;
        if (!BN_sub_word(pm1, 1))
            goto err;
        if (!BN_gcd(t, pm1, e, ctx))
            goto err;
        if (BN_is_one(t)) {
            /*
             * X9.31 specifies 8 MR and 1 Lucas test or any prime test
             * offering similar or better guarantees 50 MR is considerably
             * better.
             */
            int r = BN_check_prime(p, ctx, cb);
            if (r < 0)
                goto err;
            if (r)
                break;
        }
        if (!BN_add(p, p, p1p2))
            goto err;
    }

    BN_GENCB_call(cb, 3, 0);

    ret = 1;

 err:

    BN_CTX_end(ctx);

    return ret;
}