#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  provctx; TYPE_1__* digest; TYPE_5__* pctx; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sigprovctx; TYPE_2__* signature; } ;
struct TYPE_11__ {TYPE_3__ sig; } ;
struct TYPE_12__ {scalar_t__ operation; TYPE_4__ op; } ;
struct TYPE_9__ {int (* set_ctx_md_params ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
struct TYPE_8__ {int (* set_ctx_params ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_5__ EVP_PKEY_CTX ;
typedef  TYPE_6__ EVP_MD_CTX ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_OP_SIGNCTX ; 
 scalar_t__ EVP_PKEY_OP_VERIFYCTX ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int EVP_MD_CTX_set_params(EVP_MD_CTX *ctx, const OSSL_PARAM params[])
{
    EVP_PKEY_CTX *pctx = ctx->pctx;

    if (ctx->digest != NULL && ctx->digest->set_ctx_params != NULL)
        return ctx->digest->set_ctx_params(ctx->provctx, params);

    if (pctx != NULL
            && (pctx->operation == EVP_PKEY_OP_VERIFYCTX
                || pctx->operation == EVP_PKEY_OP_SIGNCTX)
            && pctx->op.sig.sigprovctx != NULL
            && pctx->op.sig.signature->set_ctx_md_params != NULL)
        return pctx->op.sig.signature->set_ctx_md_params(pctx->op.sig.sigprovctx,
                                                         params);
    return 0;
}