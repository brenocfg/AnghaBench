#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * sigprovctx; } ;
struct TYPE_11__ {int /*<<< orphan*/ * exchprovctx; } ;
struct TYPE_13__ {TYPE_2__ sig; TYPE_1__ kex; } ;
struct TYPE_15__ {int operation; TYPE_4__* pmeth; TYPE_3__ op; } ;
struct TYPE_14__ {int (* ctrl ) (TYPE_5__*,int,int,void*) ;int pkey_id; int /*<<< orphan*/ * digest_custom; } ;
typedef  TYPE_5__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_CTX_CTRL ; 
 scalar_t__ EVP_PKEY_CTX_IS_DERIVE_OP (TYPE_5__*) ; 
 scalar_t__ EVP_PKEY_CTX_IS_SIGNATURE_OP (TYPE_5__*) ; 
 int EVP_PKEY_OP_UNDEFINED ; 
 int /*<<< orphan*/  EVP_R_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EVP_R_INVALID_OPERATION ; 
 int /*<<< orphan*/  EVP_R_NO_OPERATION_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int legacy_ctrl_to_param (TYPE_5__*,int,int,int,int,void*) ; 
 int stub1 (TYPE_5__*,int,int,void*) ; 

int EVP_PKEY_CTX_ctrl(EVP_PKEY_CTX *ctx, int keytype, int optype,
                      int cmd, int p1, void *p2)
{
    int ret;

    if (ctx == NULL) {
        EVPerr(EVP_F_EVP_PKEY_CTX_CTRL, EVP_R_COMMAND_NOT_SUPPORTED);
        return -2;
    }

    if ((EVP_PKEY_CTX_IS_DERIVE_OP(ctx) && ctx->op.kex.exchprovctx != NULL)
            || (EVP_PKEY_CTX_IS_SIGNATURE_OP(ctx)
                && ctx->op.sig.sigprovctx != NULL))
        return legacy_ctrl_to_param(ctx, keytype, optype, cmd, p1, p2);

    if (ctx->pmeth == NULL || ctx->pmeth->ctrl == NULL) {
        EVPerr(EVP_F_EVP_PKEY_CTX_CTRL, EVP_R_COMMAND_NOT_SUPPORTED);
        return -2;
    }
    if ((keytype != -1) && (ctx->pmeth->pkey_id != keytype))
        return -1;

    /* Skip the operation checks since this is called in a very early stage */
    if (ctx->pmeth->digest_custom != NULL)
        goto doit;

    if (ctx->operation == EVP_PKEY_OP_UNDEFINED) {
        EVPerr(EVP_F_EVP_PKEY_CTX_CTRL, EVP_R_NO_OPERATION_SET);
        return -1;
    }

    if ((optype != -1) && !(ctx->operation & optype)) {
        EVPerr(EVP_F_EVP_PKEY_CTX_CTRL, EVP_R_INVALID_OPERATION);
        return -1;
    }

 doit:
    ret = ctx->pmeth->ctrl(ctx, cmd, p1, p2);

    if (ret == -2)
        EVPerr(EVP_F_EVP_PKEY_CTX_CTRL, EVP_R_COMMAND_NOT_SUPPORTED);

    return ret;
}