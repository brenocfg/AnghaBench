#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* pmeth; scalar_t__ pkey_gencb; TYPE_2__* data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pub_exp; int /*<<< orphan*/  primes; int /*<<< orphan*/  nbits; } ;
struct TYPE_7__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ RSA_PKEY_CTX ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_F4 ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int RSA_generate_multi_prime_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  evp_pkey_set_cb_translate (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  rsa_set_pss_param (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int pkey_rsa_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    RSA *rsa = NULL;
    RSA_PKEY_CTX *rctx = ctx->data;
    BN_GENCB *pcb;
    int ret;

    if (rctx->pub_exp == NULL) {
        rctx->pub_exp = BN_new();
        if (rctx->pub_exp == NULL || !BN_set_word(rctx->pub_exp, RSA_F4))
            return 0;
    }
    rsa = RSA_new();
    if (rsa == NULL)
        return 0;
    if (ctx->pkey_gencb) {
        pcb = BN_GENCB_new();
        if (pcb == NULL) {
            RSA_free(rsa);
            return 0;
        }
        evp_pkey_set_cb_translate(pcb, ctx);
    } else {
        pcb = NULL;
    }
    ret = RSA_generate_multi_prime_key(rsa, rctx->nbits, rctx->primes,
                                       rctx->pub_exp, pcb);
    BN_GENCB_free(pcb);
    if (ret > 0 && !rsa_set_pss_param(rsa, ctx)) {
        RSA_free(rsa);
        return 0;
    }
    if (ret > 0)
        EVP_PKEY_assign(pkey, ctx->pmeth->pkey_id, rsa);
    else
        RSA_free(rsa);
    return ret;
}