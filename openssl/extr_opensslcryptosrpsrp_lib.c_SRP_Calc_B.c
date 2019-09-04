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
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/ * srp_Calc_k (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

BIGNUM *SRP_Calc_B(const BIGNUM *b, const BIGNUM *N, const BIGNUM *g,
                   const BIGNUM *v)
{
    BIGNUM *kv = NULL, *gb = NULL;
    BIGNUM *B = NULL, *k = NULL;
    BN_CTX *bn_ctx;

    if (b == NULL || N == NULL || g == NULL || v == NULL ||
        (bn_ctx = BN_CTX_new()) == NULL)
        return NULL;

    if ((kv = BN_new()) == NULL ||
        (gb = BN_new()) == NULL || (B = BN_new()) == NULL)
        goto err;

    /* B = g**b + k*v */

    if (!BN_mod_exp(gb, g, b, N, bn_ctx)
        || (k = srp_Calc_k(N, g)) == NULL
        || !BN_mod_mul(kv, v, k, N, bn_ctx)
        || !BN_mod_add(B, gb, kv, N, bn_ctx)) {
        BN_free(B);
        B = NULL;
    }
 err:
    BN_CTX_free(bn_ctx);
    BN_clear_free(kv);
    BN_clear_free(gb);
    BN_free(k);
    return B;
}