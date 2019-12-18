#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/ * iqmp; int /*<<< orphan*/ * p; int /*<<< orphan*/ * q; int /*<<< orphan*/ * d; int /*<<< orphan*/ * dmq1; int /*<<< orphan*/ * dmp1; int /*<<< orphan*/ * e; int /*<<< orphan*/ * n; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_X931_derive_prime_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* BN_mod_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 

int RSA_X931_derive_ex(RSA *rsa, BIGNUM *p1, BIGNUM *p2, BIGNUM *q1,
                       BIGNUM *q2, const BIGNUM *Xp1, const BIGNUM *Xp2,
                       const BIGNUM *Xp, const BIGNUM *Xq1, const BIGNUM *Xq2,
                       const BIGNUM *Xq, const BIGNUM *e, BN_GENCB *cb)
{
    BIGNUM *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
    BN_CTX *ctx = NULL, *ctx2 = NULL;
    int ret = 0;

    if (!rsa)
        goto err;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);

    r0 = BN_CTX_get(ctx);
    r1 = BN_CTX_get(ctx);
    r2 = BN_CTX_get(ctx);
    r3 = BN_CTX_get(ctx);

    if (r3 == NULL)
        goto err;
    if (!rsa->e) {
        rsa->e = BN_dup(e);
        if (!rsa->e)
            goto err;
    } else {
        e = rsa->e;
    }

    /*
     * If not all parameters present only calculate what we can. This allows
     * test programs to output selective parameters.
     */

    if (Xp && rsa->p == NULL) {
        rsa->p = BN_new();
        if (rsa->p == NULL)
            goto err;

        if (!BN_X931_derive_prime_ex(rsa->p, p1, p2,
                                     Xp, Xp1, Xp2, e, ctx, cb))
            goto err;
    }

    if (Xq && rsa->q == NULL) {
        rsa->q = BN_new();
        if (rsa->q == NULL)
            goto err;
        if (!BN_X931_derive_prime_ex(rsa->q, q1, q2,
                                     Xq, Xq1, Xq2, e, ctx, cb))
            goto err;
    }

    if (rsa->p == NULL || rsa->q == NULL) {
        BN_CTX_end(ctx);
        BN_CTX_free(ctx);
        return 2;
    }

    /*
     * Since both primes are set we can now calculate all remaining
     * components.
     */

    /* calculate n */
    rsa->n = BN_new();
    if (rsa->n == NULL)
        goto err;
    if (!BN_mul(rsa->n, rsa->p, rsa->q, ctx))
        goto err;

    /* calculate d */
    if (!BN_sub(r1, rsa->p, BN_value_one()))
        goto err;               /* p-1 */
    if (!BN_sub(r2, rsa->q, BN_value_one()))
        goto err;               /* q-1 */
    if (!BN_mul(r0, r1, r2, ctx))
        goto err;               /* (p-1)(q-1) */

    if (!BN_gcd(r3, r1, r2, ctx))
        goto err;

    if (!BN_div(r0, NULL, r0, r3, ctx))
        goto err;               /* LCM((p-1)(q-1)) */

    ctx2 = BN_CTX_new();
    if (ctx2 == NULL)
        goto err;

    rsa->d = BN_mod_inverse(NULL, rsa->e, r0, ctx2); /* d */
    if (rsa->d == NULL)
        goto err;

    /* calculate d mod (p-1) */
    rsa->dmp1 = BN_new();
    if (rsa->dmp1 == NULL)
        goto err;
    if (!BN_mod(rsa->dmp1, rsa->d, r1, ctx))
        goto err;

    /* calculate d mod (q-1) */
    rsa->dmq1 = BN_new();
    if (rsa->dmq1 == NULL)
        goto err;
    if (!BN_mod(rsa->dmq1, rsa->d, r2, ctx))
        goto err;

    /* calculate inverse of q mod p */
    rsa->iqmp = BN_mod_inverse(NULL, rsa->q, rsa->p, ctx2);
    if (rsa->iqmp == NULL)
        goto err;

    rsa->dirty_cnt++;
    ret = 1;
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    BN_CTX_free(ctx2);

    return ret;

}