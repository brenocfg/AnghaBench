#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * sigprovctx; TYPE_1__* signature; } ;
struct TYPE_10__ {TYPE_2__ sig; } ;
struct TYPE_12__ {scalar_t__ operation; TYPE_4__* pmeth; TYPE_3__ op; } ;
struct TYPE_11__ {int (* verify ) (TYPE_5__*,unsigned char const*,size_t,unsigned char const*,size_t) ;} ;
struct TYPE_8__ {int (* verify ) (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t) ;} ;
typedef  TYPE_5__ EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_OP_VERIFY ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVP_R_OPERATON_NOT_INITIALIZED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t) ; 
 int stub2 (TYPE_5__*,unsigned char const*,size_t,unsigned char const*,size_t) ; 

int EVP_PKEY_verify(EVP_PKEY_CTX *ctx,
                    const unsigned char *sig, size_t siglen,
                    const unsigned char *tbs, size_t tbslen)
{
    int ret;

    if (ctx == NULL) {
        EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    if (ctx->operation != EVP_PKEY_OP_VERIFY) {
        EVPerr(0, EVP_R_OPERATON_NOT_INITIALIZED);
        return -1;
    }

    if (ctx->op.sig.sigprovctx == NULL)
        goto legacy;

    ret = ctx->op.sig.signature->verify(ctx->op.sig.sigprovctx, sig, siglen,
                                        tbs, tbslen);

    return ret;
 legacy:
    if (ctx->pmeth == NULL || ctx->pmeth->verify == NULL) {
        EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    return ctx->pmeth->verify(ctx, sig, siglen, tbs, tbslen);
}