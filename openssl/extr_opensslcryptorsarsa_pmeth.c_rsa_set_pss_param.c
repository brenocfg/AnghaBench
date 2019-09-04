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
struct TYPE_9__ {TYPE_1__* data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pss; } ;
struct TYPE_7__ {int saltlen; int /*<<< orphan*/ * mgf1md; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ RSA_PKEY_CTX ;
typedef  TYPE_2__ RSA ;
typedef  TYPE_3__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  pkey_ctx_is_pss (TYPE_3__*) ; 
 int /*<<< orphan*/ * rsa_pss_params_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rsa_set_pss_param(RSA *rsa, EVP_PKEY_CTX *ctx)
{
    RSA_PKEY_CTX *rctx = ctx->data;

    if (!pkey_ctx_is_pss(ctx))
        return 1;
    /* If all parameters are default values don't set pss */
    if (rctx->md == NULL && rctx->mgf1md == NULL && rctx->saltlen == -2)
        return 1;
    rsa->pss = rsa_pss_params_create(rctx->md, rctx->mgf1md,
                                     rctx->saltlen == -2 ? 0 : rctx->saltlen);
    if (rsa->pss == NULL)
        return 0;
    return 1;
}