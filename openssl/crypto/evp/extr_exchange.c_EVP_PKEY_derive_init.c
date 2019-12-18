#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int (* init ) (int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  prov; int /*<<< orphan*/ * (* newctx ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/ * exchprovctx; TYPE_5__* exchange; } ;
struct TYPE_14__ {TYPE_1__ kex; } ;
struct TYPE_16__ {void* operation; TYPE_3__* pmeth; TYPE_2__ op; int /*<<< orphan*/ * keymgmt; int /*<<< orphan*/ * pkey; int /*<<< orphan*/  propquery; int /*<<< orphan*/  libctx; int /*<<< orphan*/ * algorithm; int /*<<< orphan*/ * engine; } ;
struct TYPE_15__ {int (* derive_init ) (TYPE_4__*) ;int /*<<< orphan*/ * derive; } ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  TYPE_5__ EVP_KEYEXCH ;

/* Variables and functions */
 TYPE_5__* EVP_KEYEXCH_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KEYEXCH_free (TYPE_5__*) ; 
 int EVP_KEYEXCH_number (TYPE_5__*) ; 
 scalar_t__ EVP_KEYEXCH_provider (TYPE_5__*) ; 
 scalar_t__ EVP_KEYMGMT_provider (int /*<<< orphan*/ *) ; 
 void* EVP_PKEY_OP_DERIVE ; 
 void* EVP_PKEY_OP_UNDEFINED ; 
 int /*<<< orphan*/  EVP_R_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* evp_keymgmt_export_to_provider (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * evp_keymgmt_fetch_by_number (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evp_pkey_ctx_free_old_ops (TYPE_4__*) ; 
 int /*<<< orphan*/  ossl_provider_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,void*) ; 
 int stub3 (TYPE_4__*) ; 

int EVP_PKEY_derive_init(EVP_PKEY_CTX *ctx)
{
    int ret;
    void *provkey = NULL;
    EVP_KEYEXCH *exchange = NULL;

    if (ctx == NULL) {
        EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    evp_pkey_ctx_free_old_ops(ctx);
    ctx->operation = EVP_PKEY_OP_DERIVE;

    if (ctx->engine != NULL || ctx->algorithm == NULL)
        goto legacy;

    /*
     * Because we cleared out old ops, we shouldn't need to worry about
     * checking if exchange is already there.  Keymgmt is a different
     * matter, as it isn't tied to a specific EVP_PKEY op.
     */
    exchange = EVP_KEYEXCH_fetch(ctx->libctx, ctx->algorithm, ctx->propquery);
    if (exchange != NULL && ctx->keymgmt == NULL) {
        int name_id = EVP_KEYEXCH_number(exchange);

        ctx->keymgmt =
            evp_keymgmt_fetch_by_number(ctx->libctx, name_id, ctx->propquery);
    }

    if (ctx->keymgmt == NULL
        || exchange == NULL
        || (EVP_KEYMGMT_provider(ctx->keymgmt)
            != EVP_KEYEXCH_provider(exchange))) {
        /*
         * We don't have the full support we need with provided methods,
         * let's go see if legacy does.  Also, we don't need to free
         * ctx->keymgmt here, as it's not necessarily tied to this
         * operation.  It will be freed by EVP_PKEY_CTX_free().
         */
        EVP_KEYEXCH_free(exchange);
        goto legacy;
    }


    ctx->op.kex.exchange = exchange;

    if (ctx->pkey != NULL) {
        provkey = evp_keymgmt_export_to_provider(ctx->pkey, ctx->keymgmt, 0);
        if (provkey == NULL) {
            EVPerr(0, EVP_R_INITIALIZATION_ERROR);
            goto err;
        }
    }
    ctx->op.kex.exchprovctx = exchange->newctx(ossl_provider_ctx(exchange->prov));
    if (ctx->op.kex.exchprovctx == NULL) {
        /* The provider key can stay in the cache */
        EVPerr(0, EVP_R_INITIALIZATION_ERROR);
        goto err;
    }
    ret = exchange->init(ctx->op.kex.exchprovctx, provkey);

    return ret ? 1 : 0;
 err:
    ctx->operation = EVP_PKEY_OP_UNDEFINED;
    return 0;

 legacy:
    if (ctx == NULL || ctx->pmeth == NULL || ctx->pmeth->derive == NULL) {
        EVPerr(0, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    if (ctx->pmeth->derive_init == NULL)
        return 1;
    ret = ctx->pmeth->derive_init(ctx);
    if (ret <= 0)
        ctx->operation = EVP_PKEY_OP_UNDEFINED;
    return ret;
}