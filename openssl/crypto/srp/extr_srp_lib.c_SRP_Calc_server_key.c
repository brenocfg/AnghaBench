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
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_new () ; 

BIGNUM *SRP_Calc_server_key(const BIGNUM *A, const BIGNUM *v, const BIGNUM *u,
                            const BIGNUM *b, const BIGNUM *N)
{
    BIGNUM *tmp = NULL, *S = NULL;
    BN_CTX *bn_ctx;

    if (u == NULL || A == NULL || v == NULL || b == NULL || N == NULL)
        return NULL;

    if ((bn_ctx = BN_CTX_new()) == NULL || (tmp = BN_new()) == NULL)
        goto err;

    /* S = (A*v**u) ** b */

    if (!BN_mod_exp(tmp, v, u, N, bn_ctx))
        goto err;
    if (!BN_mod_mul(tmp, A, tmp, N, bn_ctx))
        goto err;

    S = BN_new();
    if (S != NULL && !BN_mod_exp(S, tmp, b, N, bn_ctx)) {
        BN_free(S);
        S = NULL;
    }
 err:
    BN_CTX_free(bn_ctx);
    BN_clear_free(tmp);
    return S;
}