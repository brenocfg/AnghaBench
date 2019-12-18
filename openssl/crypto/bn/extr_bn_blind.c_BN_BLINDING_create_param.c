#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* bn_mod_exp ) (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * m_ctx; int /*<<< orphan*/  const* A; int /*<<< orphan*/  const* Ai; int /*<<< orphan*/  const* mod; int /*<<< orphan*/  const* e; } ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ BN_BLINDING ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_BLINDING_free (TYPE_1__*) ; 
 TYPE_1__* BN_BLINDING_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_F_BN_BLINDING_CREATE_PARAM ; 
 int /*<<< orphan*/  BN_R_TOO_MANY_ITERATIONS ; 
 int /*<<< orphan*/  const* BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 int /*<<< orphan*/  BN_priv_rand_range_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_to_mont_fixed_top (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ int_bn_mod_inverse (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 
 int stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BN_BLINDING *BN_BLINDING_create_param(BN_BLINDING *b,
                                      const BIGNUM *e, BIGNUM *m, BN_CTX *ctx,
                                      int (*bn_mod_exp) (BIGNUM *r,
                                                         const BIGNUM *a,
                                                         const BIGNUM *p,
                                                         const BIGNUM *m,
                                                         BN_CTX *ctx,
                                                         BN_MONT_CTX *m_ctx),
                                      BN_MONT_CTX *m_ctx)
{
    int retry_counter = 32;
    BN_BLINDING *ret = NULL;

    if (b == NULL)
        ret = BN_BLINDING_new(NULL, NULL, m);
    else
        ret = b;

    if (ret == NULL)
        goto err;

    if (ret->A == NULL && (ret->A = BN_new()) == NULL)
        goto err;
    if (ret->Ai == NULL && (ret->Ai = BN_new()) == NULL)
        goto err;

    if (e != NULL) {
        BN_free(ret->e);
        ret->e = BN_dup(e);
    }
    if (ret->e == NULL)
        goto err;

    if (bn_mod_exp != NULL)
        ret->bn_mod_exp = bn_mod_exp;
    if (m_ctx != NULL)
        ret->m_ctx = m_ctx;

    do {
        int rv;
        if (!BN_priv_rand_range_ex(ret->A, ret->mod, ctx))
            goto err;
        if (int_bn_mod_inverse(ret->Ai, ret->A, ret->mod, ctx, &rv))
            break;

        /*
         * this should almost never happen for good RSA keys
         */
        if (!rv)
            goto err;

        if (retry_counter-- == 0) {
            BNerr(BN_F_BN_BLINDING_CREATE_PARAM, BN_R_TOO_MANY_ITERATIONS);
            goto err;
        }
    } while (1);

    if (ret->bn_mod_exp != NULL && ret->m_ctx != NULL) {
        if (!ret->bn_mod_exp(ret->A, ret->A, ret->e, ret->mod, ctx, ret->m_ctx))
            goto err;
    } else {
        if (!BN_mod_exp(ret->A, ret->A, ret->e, ret->mod, ctx))
            goto err;
    }

    if (ret->m_ctx != NULL) {
        if (!bn_to_mont_fixed_top(ret->Ai, ret->Ai, ret->m_ctx, ctx)
            || !bn_to_mont_fixed_top(ret->A, ret->A, ret->m_ctx, ctx))
            goto err;
    }

    return ret;
 err:
    if (b == NULL) {
        BN_BLINDING_free(ret);
        ret = NULL;
    }

    return ret;
}