#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  engine; TYPE_1__* digest; scalar_t__ md_data; int /*<<< orphan*/ * provctx; int /*<<< orphan*/ * reqdigest; int /*<<< orphan*/ * fetched_digest; int /*<<< orphan*/  pctx; } ;
struct TYPE_8__ {scalar_t__ ctx_size; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_CLEANED ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_KEEP_PKEY_CTX ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_REUSE ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_test_flags (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (TYPE_2__*,int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

int EVP_MD_CTX_reset(EVP_MD_CTX *ctx)
{
    if (ctx == NULL)
        return 1;

#ifndef FIPS_MODE
    /* TODO(3.0): Temporarily no support for EVP_DigestSign* in FIPS module */
    /*
     * pctx should be freed by the user of EVP_MD_CTX
     * if EVP_MD_CTX_FLAG_KEEP_PKEY_CTX is set
     */
    if (!EVP_MD_CTX_test_flags(ctx, EVP_MD_CTX_FLAG_KEEP_PKEY_CTX))
        EVP_PKEY_CTX_free(ctx->pctx);
#endif

    EVP_MD_free(ctx->fetched_digest);
    ctx->fetched_digest = NULL;
    ctx->reqdigest = NULL;

    if (ctx->provctx != NULL) {
        if (ctx->digest->freectx != NULL)
            ctx->digest->freectx(ctx->provctx);
        ctx->provctx = NULL;
        EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_CLEANED);
    }

    /* TODO(3.0): Remove legacy code below */

    /*
     * Don't assume ctx->md_data was cleaned in EVP_Digest_Final, because
     * sometimes only copies of the context are ever finalised.
     */
    if (ctx->digest && ctx->digest->cleanup
        && !EVP_MD_CTX_test_flags(ctx, EVP_MD_CTX_FLAG_CLEANED))
        ctx->digest->cleanup(ctx);
    if (ctx->digest && ctx->digest->ctx_size && ctx->md_data
        && !EVP_MD_CTX_test_flags(ctx, EVP_MD_CTX_FLAG_REUSE)) {
        OPENSSL_clear_free(ctx->md_data, ctx->digest->ctx_size);
    }

#if !defined(FIPS_MODE) && !defined(OPENSSL_NO_ENGINE)
    ENGINE_finish(ctx->engine);
#endif

    /* TODO(3.0): End of legacy code */

    OPENSSL_cleanse(ctx, sizeof(*ctx));

    return 1;
}