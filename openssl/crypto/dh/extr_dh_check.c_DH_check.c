#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p; int /*<<< orphan*/ * q; scalar_t__ j; scalar_t__ g; } ;
typedef  TYPE_1__ DH ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int BN_check_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_value_one () ; 
 int DH_CHECK_INVALID_J_VALUE ; 
 int DH_CHECK_INVALID_Q_VALUE ; 
 int DH_CHECK_P_NOT_PRIME ; 
 int DH_CHECK_P_NOT_SAFE_PRIME ; 
 int DH_CHECK_Q_NOT_PRIME ; 
 int DH_NOT_SUITABLE_GENERATOR ; 
 int /*<<< orphan*/  DH_check_params (TYPE_1__ const*,int*) ; 

int DH_check(const DH *dh, int *ret)
{
    int ok = 0, r;
    BN_CTX *ctx = NULL;
    BIGNUM *t1 = NULL, *t2 = NULL;

    if (!DH_check_params(dh, ret))
        return 0;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);
    t1 = BN_CTX_get(ctx);
    t2 = BN_CTX_get(ctx);
    if (t2 == NULL)
        goto err;

    if (dh->q) {
        if (BN_cmp(dh->g, BN_value_one()) <= 0)
            *ret |= DH_NOT_SUITABLE_GENERATOR;
        else if (BN_cmp(dh->g, dh->p) >= 0)
            *ret |= DH_NOT_SUITABLE_GENERATOR;
        else {
            /* Check g^q == 1 mod p */
            if (!BN_mod_exp(t1, dh->g, dh->q, dh->p, ctx))
                goto err;
            if (!BN_is_one(t1))
                *ret |= DH_NOT_SUITABLE_GENERATOR;
        }
        r = BN_check_prime(dh->q, ctx, NULL);
        if (r < 0)
            goto err;
        if (!r)
            *ret |= DH_CHECK_Q_NOT_PRIME;
        /* Check p == 1 mod q  i.e. q divides p - 1 */
        if (!BN_div(t1, t2, dh->p, dh->q, ctx))
            goto err;
        if (!BN_is_one(t2))
            *ret |= DH_CHECK_INVALID_Q_VALUE;
        if (dh->j && BN_cmp(dh->j, t1))
            *ret |= DH_CHECK_INVALID_J_VALUE;
    }

    r = BN_check_prime(dh->p, ctx, NULL);
    if (r < 0)
        goto err;
    if (!r)
        *ret |= DH_CHECK_P_NOT_PRIME;
    else if (!dh->q) {
        if (!BN_rshift1(t1, dh->p))
            goto err;
        r = BN_check_prime(t1, ctx, NULL);
        if (r < 0)
            goto err;
        if (!r)
            *ret |= DH_CHECK_P_NOT_SAFE_PRIME;
    }
    ok = 1;
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ok;
}