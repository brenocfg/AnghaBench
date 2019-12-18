#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  engine; scalar_t__ cipher_data; TYPE_1__* cipher; int /*<<< orphan*/ * fetched_cipher; int /*<<< orphan*/ * provctx; } ;
struct TYPE_6__ {scalar_t__ ctx_size; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OPENSSL_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

int EVP_CIPHER_CTX_reset(EVP_CIPHER_CTX *ctx)
{
    if (ctx == NULL)
        return 1;

    if (ctx->cipher == NULL || ctx->cipher->prov == NULL)
        goto legacy;

    if (ctx->provctx != NULL) {
        if (ctx->cipher->freectx != NULL)
            ctx->cipher->freectx(ctx->provctx);
        ctx->provctx = NULL;
    }
    if (ctx->fetched_cipher != NULL)
        EVP_CIPHER_free(ctx->fetched_cipher);
    memset(ctx, 0, sizeof(*ctx));

    return 1;

    /* TODO(3.0): Remove legacy code below */
 legacy:

    if (ctx->cipher != NULL) {
        if (ctx->cipher->cleanup && !ctx->cipher->cleanup(ctx))
            return 0;
        /* Cleanse cipher context data */
        if (ctx->cipher_data && ctx->cipher->ctx_size)
            OPENSSL_cleanse(ctx->cipher_data, ctx->cipher->ctx_size);
    }
    OPENSSL_free(ctx->cipher_data);
#if !defined(OPENSSL_NO_ENGINE) && !defined(FIPS_MODE)
    ENGINE_finish(ctx->engine);
#endif
    memset(ctx, 0, sizeof(*ctx));
    return 1;
}