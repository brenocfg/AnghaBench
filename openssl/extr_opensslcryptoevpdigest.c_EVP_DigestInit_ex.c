#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int type; scalar_t__ ctx_size; int (* dinit ) (int /*<<< orphan*/ *) ;int (* init ) (TYPE_1__*) ;int /*<<< orphan*/  update; int /*<<< orphan*/ * prov; int /*<<< orphan*/ * (* newctx ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int flags; TYPE_2__ const* digest; int /*<<< orphan*/ * pctx; int /*<<< orphan*/ * md_data; int /*<<< orphan*/  update; int /*<<< orphan*/ * engine; int /*<<< orphan*/ * provctx; TYPE_2__ const* fetched_digest; TYPE_2__ const* reqdigest; } ;
typedef  TYPE_1__ EVP_MD_CTX ;
typedef  TYPE_2__ const EVP_MD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 TYPE_2__ const* ENGINE_get_digest (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ENGINE_get_digest_engine (int) ; 
 int /*<<< orphan*/  ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_DIGESTINIT_EX ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_CLEANED ; 
 int EVP_MD_CTX_FLAG_NO_INIT ; 
 int /*<<< orphan*/  EVP_MD_CTX_clear_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ const* EVP_MD_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EVP_MD_meth_free (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_DIGESTINIT ; 
 int EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_TYPE_SIG ; 
 int /*<<< orphan*/  EVP_R_INITIALIZATION_ERROR ; 
 int /*<<< orphan*/  EVP_R_NO_DIGEST_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NID_md2 129 
#define  NID_sha256 128 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (scalar_t__) ; 
 int /*<<< orphan*/  ossl_provider_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_1__*) ; 

int EVP_DigestInit_ex(EVP_MD_CTX *ctx, const EVP_MD *type, ENGINE *impl)
{
    EVP_MD *provmd;
    ENGINE *tmpimpl = NULL;

    EVP_MD_CTX_clear_flags(ctx, EVP_MD_CTX_FLAG_CLEANED);

    if (type != NULL)
        ctx->reqdigest = type;

    /* TODO(3.0): Legacy work around code below. Remove this */
#ifndef OPENSSL_NO_ENGINE
    /*
     * Whether it's nice or not, "Inits" can be used on "Final"'d contexts so
     * this context may already have an ENGINE! Try to avoid releasing the
     * previous handle, re-querying for an ENGINE, and having a
     * reinitialisation, when it may all be unnecessary.
     */
    if (ctx->engine && ctx->digest &&
        (type == NULL || (type->type == ctx->digest->type)))
        goto skip_to_init;

    if (type != NULL && impl == NULL)
        tmpimpl = ENGINE_get_digest_engine(type->type);
#endif

    /*
     * If there are engines involved or if we're being used as part of
     * EVP_DigestSignInit then we should use legacy handling for now.
     */
    if (ctx->engine != NULL
            || impl != NULL
            || tmpimpl != NULL
            || ctx->pctx != NULL
            || (ctx->flags & EVP_MD_CTX_FLAG_NO_INIT) != 0) {
        if (ctx->digest == ctx->fetched_digest)
            ctx->digest = NULL;
        EVP_MD_meth_free(ctx->fetched_digest);
        ctx->fetched_digest = NULL;
        goto legacy;
    }

    if (type->prov == NULL) {
        switch(type->type) {
        case NID_sha256:
        case NID_md2:
            break;
        default:
            goto legacy;
        }
    }

    if (ctx->digest != NULL && ctx->digest->ctx_size > 0) {
        OPENSSL_clear_free(ctx->md_data, ctx->digest->ctx_size);
        ctx->md_data = NULL;
    }

    /* TODO(3.0): Start of non-legacy code below */

    if (type->prov == NULL) {
        provmd = EVP_MD_fetch(NULL, OBJ_nid2sn(type->type), "");
        if (provmd == NULL) {
            EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }
        type = provmd;
        EVP_MD_meth_free(ctx->fetched_digest);
        ctx->fetched_digest = provmd;
    }

    ctx->digest = type;
    if (ctx->provctx == NULL) {
        ctx->provctx = ctx->digest->newctx(ossl_provider_ctx(type->prov));
        if (ctx->provctx == NULL) {
            EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
            return 0;
        }
    }

    if (ctx->digest->dinit == NULL) {
        EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
        return 0;
    }

    return ctx->digest->dinit(ctx->provctx);

    /* TODO(3.0): Remove legacy code below */
 legacy:

#ifndef OPENSSL_NO_ENGINE
    if (type) {
        /*
         * Ensure an ENGINE left lying around from last time is cleared (the
         * previous check attempted to avoid this if the same ENGINE and
         * EVP_MD could be used).
         */
        ENGINE_finish(ctx->engine);
        if (impl != NULL) {
            if (!ENGINE_init(impl)) {
                EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
                return 0;
            }
        } else {
            /* Ask if an ENGINE is reserved for this job */
            impl = tmpimpl;
        }
        if (impl != NULL) {
            /* There's an ENGINE for this job ... (apparently) */
            const EVP_MD *d = ENGINE_get_digest(impl, type->type);

            if (d == NULL) {
                EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_INITIALIZATION_ERROR);
                ENGINE_finish(impl);
                return 0;
            }
            /* We'll use the ENGINE's private digest definition */
            type = d;
            /*
             * Store the ENGINE functional reference so we know 'type' came
             * from an ENGINE and we need to release it when done.
             */
            ctx->engine = impl;
        } else
            ctx->engine = NULL;
    } else {
        if (!ctx->digest) {
            EVPerr(EVP_F_EVP_DIGESTINIT_EX, EVP_R_NO_DIGEST_SET);
            return 0;
        }
        type = ctx->digest;
    }
#endif
    if (ctx->digest != type) {
        if (ctx->digest && ctx->digest->ctx_size) {
            OPENSSL_clear_free(ctx->md_data, ctx->digest->ctx_size);
            ctx->md_data = NULL;
        }
        ctx->digest = type;
        if (!(ctx->flags & EVP_MD_CTX_FLAG_NO_INIT) && type->ctx_size) {
            ctx->update = type->update;
            ctx->md_data = OPENSSL_zalloc(type->ctx_size);
            if (ctx->md_data == NULL) {
                EVPerr(EVP_F_EVP_DIGESTINIT_EX, ERR_R_MALLOC_FAILURE);
                return 0;
            }
        }
    }
#ifndef OPENSSL_NO_ENGINE
 skip_to_init:
#endif
    if (ctx->pctx) {
        int r;
        r = EVP_PKEY_CTX_ctrl(ctx->pctx, -1, EVP_PKEY_OP_TYPE_SIG,
                              EVP_PKEY_CTRL_DIGESTINIT, 0, ctx);
        if (r <= 0 && (r != -2))
            return 0;
    }
    if (ctx->flags & EVP_MD_CTX_FLAG_NO_INIT)
        return 1;
    return ctx->digest->init(ctx);
}