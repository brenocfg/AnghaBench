#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {TYPE_6__* signature; int /*<<< orphan*/ * sigprovctx; } ;
struct TYPE_10__ {TYPE_9__* exchange; int /*<<< orphan*/ * exchprovctx; } ;
struct TYPE_12__ {TYPE_2__ sig; TYPE_1__ kex; } ;
struct TYPE_13__ {TYPE_3__ op; } ;
typedef  TYPE_4__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KEYEXCH_free (TYPE_9__*) ; 
 scalar_t__ EVP_PKEY_CTX_IS_DERIVE_OP (TYPE_4__*) ; 
 scalar_t__ EVP_PKEY_CTX_IS_SIGNATURE_OP (TYPE_4__*) ; 
 int /*<<< orphan*/  EVP_SIGNATURE_free (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void evp_pkey_ctx_free_old_ops(EVP_PKEY_CTX *ctx)
{
    if (EVP_PKEY_CTX_IS_DERIVE_OP(ctx)) {
        if (ctx->op.kex.exchprovctx != NULL && ctx->op.kex.exchange != NULL)
            ctx->op.kex.exchange->freectx(ctx->op.kex.exchprovctx);
        EVP_KEYEXCH_free(ctx->op.kex.exchange);
        ctx->op.kex.exchprovctx = NULL;
        ctx->op.kex.exchange = NULL;
    } else if (EVP_PKEY_CTX_IS_SIGNATURE_OP(ctx)) {
        if (ctx->op.sig.sigprovctx != NULL && ctx->op.sig.signature != NULL)
            ctx->op.sig.signature->freectx(ctx->op.sig.sigprovctx);
        EVP_SIGNATURE_free(ctx->op.sig.signature);
        ctx->op.sig.sigprovctx = NULL;
        ctx->op.sig.signature = NULL;
    }
}