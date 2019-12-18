#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * sigprovctx; TYPE_4__* signature; } ;
struct TYPE_16__ {TYPE_1__ sig; } ;
struct TYPE_19__ {int operation; TYPE_3__* pmeth; TYPE_2__ op; int /*<<< orphan*/ * keymgmt; int /*<<< orphan*/ * pkey; int /*<<< orphan*/  propquery; int /*<<< orphan*/  libctx; int /*<<< orphan*/ * algorithm; } ;
struct TYPE_18__ {int (* sign_init ) (int /*<<< orphan*/ *,void*) ;int (* verify_init ) (int /*<<< orphan*/ *,void*) ;int (* verify_recover_init ) (int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  prov; int /*<<< orphan*/ * (* newctx ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int (* sign_init ) (TYPE_5__*) ;int (* verify_init ) (TYPE_5__*) ;int (* verify_recover_init ) (TYPE_5__*) ;int /*<<< orphan*/ * verify_recover; int /*<<< orphan*/ * verify; int /*<<< orphan*/ * sign; } ;
typedef  TYPE_4__ EVP_SIGNATURE ;
typedef  TYPE_5__ EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ EVP_KEYMGMT_provider (int /*<<< orphan*/ *) ; 
#define  EVP_PKEY_OP_SIGN 130 
 int EVP_PKEY_OP_UNDEFINED ; 
#define  EVP_PKEY_OP_VERIFY 129 
#define  EVP_PKEY_OP_VERIFYRECOVER 128 
 int /*<<< orphan*/  EVP_R_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 TYPE_4__* EVP_SIGNATURE_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_SIGNATURE_free (TYPE_4__*) ; 
 int EVP_SIGNATURE_number (TYPE_4__*) ; 
 scalar_t__ EVP_SIGNATURE_provider (TYPE_4__*) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* evp_keymgmt_export_to_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * evp_keymgmt_fetch_by_number (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evp_pkey_ctx_free_old_ops (TYPE_5__*) ; 
 int /*<<< orphan*/  ossl_provider_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,void*) ; 
 int stub3 (int /*<<< orphan*/ *,void*) ; 
 int stub4 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 
 int stub6 (TYPE_5__*) ; 
 int stub7 (TYPE_5__*) ; 
 int stub8 (TYPE_5__*) ; 

__attribute__((used)) static int evp_pkey_signature_init(EVP_PKEY_CTX *ctx, int operation)
{
    int ret = 0;
    void *provkey = NULL;
    EVP_SIGNATURE *signature = NULL;

    if (ctx == NULL) {
        EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    evp_pkey_ctx_free_old_ops(ctx);
    ctx->operation = operation;

    if (ctx->algorithm == NULL)
        goto legacy;

    /*
     * Because we cleared out old ops, we shouldn't need to worry about
     * checking if signature is already there.  Keymgmt is a different
     * matter, as it isn't tied to a specific EVP_PKEY op.
     */
    signature = EVP_SIGNATURE_fetch(ctx->libctx, ctx->algorithm,
                                    ctx->propquery);
    if (signature != NULL && ctx->keymgmt == NULL) {
        int name_id = EVP_SIGNATURE_number(signature);

        ctx->keymgmt = evp_keymgmt_fetch_by_number(ctx->libctx, name_id,
                                                   ctx->propquery);
    }

    if (ctx->keymgmt == NULL
        || signature == NULL
        || (EVP_KEYMGMT_provider(ctx->keymgmt)
            != EVP_SIGNATURE_provider(signature))) {
        /*
         * We don't have the full support we need with provided methods,
         * let's go see if legacy does.  Also, we don't need to free
         * ctx->keymgmt here, as it's not necessarily tied to this
         * operation.  It will be freed by EVP_PKEY_CTX_free().
         */
        EVP_SIGNATURE_free(signature);
        goto legacy;
    }

    ctx->op.sig.signature = signature;

    if (ctx->pkey != NULL) {
        provkey =
            evp_keymgmt_export_to_provider(ctx->pkey, ctx->keymgmt, 0);
        if (provkey == NULL) {
            EVPerr(0, EVP_R_INITIALIZATION_ERROR);
            goto err;
        }
    }
    ctx->op.sig.sigprovctx = signature->newctx(ossl_provider_ctx(signature->prov));
    if (ctx->op.sig.sigprovctx == NULL) {
        /* The provider key can stay in the cache */
        EVPerr(0, EVP_R_INITIALIZATION_ERROR);
        goto err;
    }

    switch (operation) {
    case EVP_PKEY_OP_SIGN:
        if (signature->sign_init == NULL) {
            EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
            ret = -2;
            goto err;
        }
        ret = signature->sign_init(ctx->op.sig.sigprovctx, provkey);
        break;
    case EVP_PKEY_OP_VERIFY:
        if (signature->verify_init == NULL) {
            EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
            ret = -2;
            goto err;
        }
        ret = signature->verify_init(ctx->op.sig.sigprovctx, provkey);
        break;
    case EVP_PKEY_OP_VERIFYRECOVER:
        if (signature->verify_recover_init == NULL) {
            EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
            ret = -2;
            goto err;
        }
        ret = signature->verify_recover_init(ctx->op.sig.sigprovctx, provkey);
        break;
    default:
        EVPerr(0, EVP_R_INITIALIZATION_ERROR);
        goto err;
    }

    if (ret <= 0) {
        signature->freectx(ctx->op.sig.sigprovctx);
        ctx->op.sig.sigprovctx = NULL;
        goto err;
    }
    return 1;

 legacy:
    if (ctx->pmeth == NULL
            || (operation == EVP_PKEY_OP_SIGN && ctx->pmeth->sign == NULL)
            || (operation == EVP_PKEY_OP_VERIFY && ctx->pmeth->verify == NULL)
            || (operation == EVP_PKEY_OP_VERIFYRECOVER
                && ctx->pmeth->verify_recover == NULL)) {
        EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    switch (operation) {
    case EVP_PKEY_OP_SIGN:
        if (ctx->pmeth->sign_init == NULL)
            return 1;
        ret = ctx->pmeth->sign_init(ctx);
        break;
    case EVP_PKEY_OP_VERIFY:
        if (ctx->pmeth->verify_init == NULL)
            return 1;
        ret = ctx->pmeth->verify_init(ctx);
        break;
    case EVP_PKEY_OP_VERIFYRECOVER:
        if (ctx->pmeth->verify_recover_init == NULL)
            return 1;
        ret = ctx->pmeth->verify_recover_init(ctx);
        break;
    default:
        EVPerr(0, EVP_R_INITIALIZATION_ERROR);
        goto err;
    }
    if (ret <= 0)
        goto err;
    return ret;

 err:
    ctx->operation = EVP_PKEY_OP_UNDEFINED;
    return ret;
}