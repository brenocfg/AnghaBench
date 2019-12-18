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
struct TYPE_6__ {int /*<<< orphan*/  operation; TYPE_1__* pmeth; } ;
struct TYPE_5__ {int (* keygen_init ) (TYPE_2__*) ;int /*<<< orphan*/  keygen; } ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_KEYGEN_INIT ; 
 int /*<<< orphan*/  EVP_PKEY_OP_KEYGEN ; 
 int /*<<< orphan*/  EVP_PKEY_OP_UNDEFINED ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 

int EVP_PKEY_keygen_init(EVP_PKEY_CTX *ctx)
{
    int ret;
    if (!ctx || !ctx->pmeth || !ctx->pmeth->keygen) {
        EVPerr(EVP_F_EVP_PKEY_KEYGEN_INIT,
               EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }
    ctx->operation = EVP_PKEY_OP_KEYGEN;
    if (!ctx->pmeth->keygen_init)
        return 1;
    ret = ctx->pmeth->keygen_init(ctx);
    if (ret <= 0)
        ctx->operation = EVP_PKEY_OP_UNDEFINED;
    return ret;
}