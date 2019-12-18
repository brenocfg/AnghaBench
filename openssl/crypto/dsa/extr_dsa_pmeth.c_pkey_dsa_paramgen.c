#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pmd; int /*<<< orphan*/  qbits; int /*<<< orphan*/  nbits; } ;
struct TYPE_5__ {scalar_t__ pkey_gencb; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ DSA_PKEY_CTX ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/  EVP_PKEY_assign_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dsa_builtin_paramgen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evp_pkey_set_cb_translate (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int pkey_dsa_paramgen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    DSA *dsa = NULL;
    DSA_PKEY_CTX *dctx = ctx->data;
    BN_GENCB *pcb;
    int ret;

    if (ctx->pkey_gencb) {
        pcb = BN_GENCB_new();
        if (pcb == NULL)
            return 0;
        evp_pkey_set_cb_translate(pcb, ctx);
    } else
        pcb = NULL;
    dsa = DSA_new();
    if (dsa == NULL) {
        BN_GENCB_free(pcb);
        return 0;
    }
    ret = dsa_builtin_paramgen(dsa, dctx->nbits, dctx->qbits, dctx->pmd,
                               NULL, 0, NULL, NULL, NULL, pcb);
    BN_GENCB_free(pcb);
    if (ret)
        EVP_PKEY_assign_DSA(pkey, dsa);
    else
        DSA_free(dsa);
    return ret;
}