#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * sigprovctx; TYPE_3__* signature; } ;
struct TYPE_11__ {int /*<<< orphan*/ * exchprovctx; TYPE_1__* exchange; } ;
struct TYPE_14__ {TYPE_4__ sig; TYPE_2__ kex; } ;
struct TYPE_15__ {TYPE_5__ op; } ;
struct TYPE_12__ {int (* set_ctx_params ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int (* set_ctx_params ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_6__ EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_CTX_IS_DERIVE_OP (TYPE_6__*) ; 
 scalar_t__ EVP_PKEY_CTX_IS_SIGNATURE_OP (TYPE_6__*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EVP_PKEY_CTX_set_params(EVP_PKEY_CTX *ctx, OSSL_PARAM *params)
{
    if (EVP_PKEY_CTX_IS_DERIVE_OP(ctx)
            && ctx->op.kex.exchprovctx != NULL
            && ctx->op.kex.exchange != NULL
            && ctx->op.kex.exchange->set_ctx_params != NULL)
        return ctx->op.kex.exchange->set_ctx_params(ctx->op.kex.exchprovctx,
                                                    params);
    if (EVP_PKEY_CTX_IS_SIGNATURE_OP(ctx)
            && ctx->op.sig.sigprovctx != NULL
            && ctx->op.sig.signature != NULL
            && ctx->op.sig.signature->set_ctx_params != NULL)
        return ctx->op.sig.signature->set_ctx_params(ctx->op.sig.sigprovctx,
                                                     params);
    return 0;
}