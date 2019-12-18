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
struct TYPE_3__ {int /*<<< orphan*/ * dmp1; int /*<<< orphan*/ * dmq1; int /*<<< orphan*/ * iqmp; int /*<<< orphan*/ * n; int /*<<< orphan*/ * d; int /*<<< orphan*/ * e; int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/ * p; int /*<<< orphan*/  const* q; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_mod_inverse (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 void* BN_secure_new () ; 
 int rsa_get_lcm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int rsa_sp800_56b_derive_params_from_pq(RSA *rsa, int nbits,
                                        const BIGNUM *e, BN_CTX *ctx)
{
    int ret = -1;
    BIGNUM *p1, *q1, *lcm, *p1q1, *gcd;

    BN_CTX_start(ctx);
    p1 = BN_CTX_get(ctx);
    q1 = BN_CTX_get(ctx);
    lcm = BN_CTX_get(ctx);
    p1q1 = BN_CTX_get(ctx);
    gcd = BN_CTX_get(ctx);
    if (gcd == NULL)
        goto err;

    /* LCM((p-1, q-1)) */
    if (rsa_get_lcm(ctx, rsa->p, rsa->q, lcm, gcd, p1, q1, p1q1) != 1)
        goto err;

    /* copy e */
    BN_free(rsa->e);
    rsa->e = BN_dup(e);
    if (rsa->e == NULL)
        goto err;

    BN_clear_free(rsa->d);
    /* (Step 3) d = (e^-1) mod (LCM(p-1, q-1)) */
    rsa->d = BN_secure_new();
    if (rsa->d == NULL || BN_mod_inverse(rsa->d, e, lcm, ctx) == NULL)
        goto err;

    /* (Step 3) return an error if d is too small */
    if (BN_num_bits(rsa->d) <= (nbits >> 1)) {
        ret = 0;
        goto err;
    }

    /* (Step 4) n = pq */
    if (rsa->n == NULL)
        rsa->n = BN_new();
    if (rsa->n == NULL || !BN_mul(rsa->n, rsa->p, rsa->q, ctx))
        goto err;

    /* (Step 5a) dP = d mod (p-1) */
    if (rsa->dmp1 == NULL)
        rsa->dmp1 = BN_new();
    if (rsa->dmp1 == NULL || !BN_mod(rsa->dmp1, rsa->d, p1, ctx))
        goto err;

    /* (Step 5b) dQ = d mod (q-1) */
    if (rsa->dmq1 == NULL)
        rsa->dmq1 = BN_secure_new();
    if (rsa->dmq1 == NULL || !BN_mod(rsa->dmq1, rsa->d, q1, ctx))
        goto err;

    /* (Step 5c) qInv = (inverse of q) mod p */
    BN_free(rsa->iqmp);
    rsa->iqmp = BN_secure_new();
    if (rsa->iqmp == NULL
            || BN_mod_inverse(rsa->iqmp, rsa->q, rsa->p, ctx) == NULL)
        goto err;

    rsa->dirty_cnt++;
    ret = 1;
err:
    if (ret != 1) {
        BN_free(rsa->e);
        rsa->e = NULL;
        BN_free(rsa->d);
        rsa->d = NULL;
        BN_free(rsa->n);
        rsa->n = NULL;
        BN_free(rsa->iqmp);
        rsa->iqmp = NULL;
        BN_free(rsa->dmq1);
        rsa->dmq1 = NULL;
        BN_free(rsa->dmp1);
        rsa->dmp1 = NULL;
    }
    BN_clear(p1);
    BN_clear(q1);
    BN_clear(lcm);
    BN_clear(p1q1);
    BN_clear(gcd);

    BN_CTX_end(ctx);
    return ret;
}