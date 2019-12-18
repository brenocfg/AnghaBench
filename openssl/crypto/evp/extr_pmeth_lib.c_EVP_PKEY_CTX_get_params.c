#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * sigprovctx; TYPE_2__* signature; } ;
struct TYPE_9__ {TYPE_1__ sig; } ;
struct TYPE_10__ {TYPE_3__ op; } ;
struct TYPE_8__ {int (* get_ctx_params ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_4__ EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_CTX_IS_SIGNATURE_OP (TYPE_4__*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EVP_PKEY_CTX_get_params(EVP_PKEY_CTX *ctx, OSSL_PARAM *params)
{
    if (EVP_PKEY_CTX_IS_SIGNATURE_OP(ctx)
            && ctx->op.sig.sigprovctx != NULL
            && ctx->op.sig.signature != NULL
            && ctx->op.sig.signature->get_ctx_params != NULL)
        return ctx->op.sig.signature->get_ctx_params(ctx->op.sig.sigprovctx,
                                                     params);
    return 0;
}