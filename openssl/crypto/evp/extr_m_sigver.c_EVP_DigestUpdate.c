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
struct TYPE_12__ {TYPE_4__* pctx; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sigprovctx; TYPE_1__* signature; } ;
struct TYPE_9__ {TYPE_3__ sig; } ;
struct TYPE_11__ {scalar_t__ operation; TYPE_2__ op; } ;
struct TYPE_8__ {int (* digest_verify_update ) (int /*<<< orphan*/ *,void const*,size_t) ;} ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  TYPE_5__ EVP_MD_CTX ;

/* Variables and functions */
 int EVP_DigestUpdate (TYPE_5__*,void const*,size_t) ; 
 scalar_t__ EVP_PKEY_OP_VERIFYCTX ; 
 int stub1 (int /*<<< orphan*/ *,void const*,size_t) ; 

int EVP_DigestVerifyUpdate(EVP_MD_CTX *ctx, const void *data, size_t dsize)
{
    EVP_PKEY_CTX *pctx = ctx->pctx;

    if (pctx == NULL
            || pctx->operation != EVP_PKEY_OP_VERIFYCTX
            || pctx->op.sig.sigprovctx == NULL
            || pctx->op.sig.signature == NULL)
        goto legacy;

    return pctx->op.sig.signature->digest_verify_update(pctx->op.sig.sigprovctx,
                                                        data, dsize);

 legacy:
    return EVP_DigestUpdate(ctx, data, dsize);
}