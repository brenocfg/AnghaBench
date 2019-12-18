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
struct TYPE_3__ {int /*<<< orphan*/  n; int /*<<< orphan*/  d; int /*<<< orphan*/  e; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RSA_F_RSA_SP800_56B_PAIRWISE_TEST ; 
 int /*<<< orphan*/  RSA_R_PAIRWISE_TEST_FAILURE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rsa_sp800_56b_pairwise_test(RSA *rsa, BN_CTX *ctx)
{
    int ret = 0;
    BIGNUM *k, *tmp;

    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    k = BN_CTX_get(ctx);
    if (k == NULL)
        goto err;

    ret = (BN_set_word(k, 2)
          && BN_mod_exp(tmp, k, rsa->e, rsa->n, ctx)
          && BN_mod_exp(tmp, tmp, rsa->d, rsa->n, ctx)
          && BN_cmp(k, tmp) == 0);
    if (ret == 0)
        RSAerr(RSA_F_RSA_SP800_56B_PAIRWISE_TEST, RSA_R_PAIRWISE_TEST_FAILURE);
err:
    BN_CTX_end(ctx);
    return ret;
}