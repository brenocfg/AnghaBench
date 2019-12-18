#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * sigprovctx; } ;
struct TYPE_11__ {TYPE_1__ sig; } ;
struct TYPE_14__ {scalar_t__ operation; TYPE_2__ op; } ;
struct TYPE_13__ {int (* update ) (TYPE_4__*,void const*,size_t) ;int /*<<< orphan*/  provctx; TYPE_3__* digest; TYPE_6__* pctx; } ;
struct TYPE_12__ {int (* dupdate ) (int /*<<< orphan*/ ,void const*,size_t) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_4__ EVP_MD_CTX ;

/* Variables and functions */
 int EVP_DigestSignUpdate (TYPE_4__*,void const*,size_t) ; 
 int EVP_DigestVerifyUpdate (TYPE_4__*,void const*,size_t) ; 
 int /*<<< orphan*/  EVP_F_EVP_DIGESTUPDATE ; 
 scalar_t__ EVP_PKEY_CTX_IS_SIGNATURE_OP (TYPE_6__*) ; 
 scalar_t__ EVP_PKEY_OP_SIGNCTX ; 
 scalar_t__ EVP_PKEY_OP_VERIFYCTX ; 
 int /*<<< orphan*/  EVP_R_UPDATE_ERROR ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,void const*,size_t) ; 
 int stub2 (TYPE_4__*,void const*,size_t) ; 

int EVP_DigestUpdate(EVP_MD_CTX *ctx, const void *data, size_t count)
{
    if (count == 0)
        return 1;

    if (ctx->pctx != NULL
            && EVP_PKEY_CTX_IS_SIGNATURE_OP(ctx->pctx)
            && ctx->pctx->op.sig.sigprovctx != NULL) {
        /*
         * Prior to OpenSSL 3.0 EVP_DigestSignUpdate() and
         * EVP_DigestVerifyUpdate() were just macros for EVP_DigestUpdate().
         * Some code calls EVP_DigestUpdate() directly even when initialised
         * with EVP_DigestSignInit_ex() or EVP_DigestVerifyInit_ex(), so we
         * detect that and redirect to the correct EVP_Digest*Update() function
         */
        if (ctx->pctx->operation == EVP_PKEY_OP_SIGNCTX)
            return EVP_DigestSignUpdate(ctx, data, count);
        if (ctx->pctx->operation == EVP_PKEY_OP_VERIFYCTX)
            return EVP_DigestVerifyUpdate(ctx, data, count);
        EVPerr(EVP_F_EVP_DIGESTUPDATE, EVP_R_UPDATE_ERROR);
        return 0;
    }

    if (ctx->digest == NULL || ctx->digest->prov == NULL)
        goto legacy;

    if (ctx->digest->dupdate == NULL) {
        EVPerr(EVP_F_EVP_DIGESTUPDATE, EVP_R_UPDATE_ERROR);
        return 0;
    }
    return ctx->digest->dupdate(ctx->provctx, data, count);

    /* TODO(3.0): Remove legacy code below */
 legacy:
    return ctx->update(ctx, data, count);
}