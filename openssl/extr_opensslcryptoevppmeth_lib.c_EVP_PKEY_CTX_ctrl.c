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
struct TYPE_6__ {int operation; TYPE_1__* pmeth; } ;
struct TYPE_5__ {int (* ctrl ) (TYPE_2__*,int,int,void*) ;int pkey_id; int /*<<< orphan*/ * digest_custom; } ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_CTX_CTRL ; 
 int EVP_PKEY_OP_UNDEFINED ; 
 int /*<<< orphan*/  EVP_R_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  EVP_R_INVALID_OPERATION ; 
 int /*<<< orphan*/  EVP_R_NO_OPERATION_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int,int,void*) ; 

int EVP_PKEY_CTX_ctrl(EVP_PKEY_CTX *ctx, int keytype, int optype,
                      int cmd, int p1, void *p2)
{
    int ret;

    if (!ctx || !ctx->pmeth || !ctx->pmeth->ctrl) {
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