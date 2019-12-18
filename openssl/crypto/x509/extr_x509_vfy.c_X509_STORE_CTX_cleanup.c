#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ex_data; int /*<<< orphan*/ * chain; int /*<<< orphan*/ * tree; int /*<<< orphan*/ * param; int /*<<< orphan*/ * parent; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ X509_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_X509_STORE_CTX ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free ; 
 int /*<<< orphan*/  X509_policy_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void X509_STORE_CTX_cleanup(X509_STORE_CTX *ctx)
{
    /*
     * We need to be idempotent because, unfortunately, free() also calls
     * cleanup(), so the natural call sequence new(), init(), cleanup(), free()
     * calls cleanup() for the same object twice!  Thus we must zero the
     * pointers below after they're freed!
     */
    /* Seems to always be 0 in OpenSSL, do this at most once. */
    if (ctx->cleanup != NULL) {
        ctx->cleanup(ctx);
        ctx->cleanup = NULL;
    }
    if (ctx->param != NULL) {
        if (ctx->parent == NULL)
            X509_VERIFY_PARAM_free(ctx->param);
        ctx->param = NULL;
    }
    X509_policy_tree_free(ctx->tree);
    ctx->tree = NULL;
    sk_X509_pop_free(ctx->chain, X509_free);
    ctx->chain = NULL;
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_X509_STORE_CTX, ctx, &(ctx->ex_data));
    memset(&ctx->ex_data, 0, sizeof(ctx->ex_data));
}