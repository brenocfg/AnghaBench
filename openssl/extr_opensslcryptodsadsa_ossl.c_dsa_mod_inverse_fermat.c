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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 scalar_t__ BN_set_word (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BIGNUM *dsa_mod_inverse_fermat(const BIGNUM *k, const BIGNUM *q,
                                      BN_CTX *ctx)
{
    BIGNUM *res = NULL;
    BIGNUM *r, *e;

    if ((r = BN_new()) == NULL)
        return NULL;

    BN_CTX_start(ctx);
    if ((e = BN_CTX_get(ctx)) != NULL
            && BN_set_word(r, 2)
            && BN_sub(e, q, r)
            && BN_mod_exp_mont(r, k, e, q, ctx, NULL))
        res = r;
    else
        BN_free(r);
    BN_CTX_end(ctx);
    return res;
}