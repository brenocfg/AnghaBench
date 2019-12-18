#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* dyn_indexes; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * oncelock; int /*<<< orphan*/  data; int /*<<< orphan*/ ** index_locks; } ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_OPENSSL_CTX ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 void* CRYPTO_THREAD_lock_new () ; 
 size_t OPENSSL_CTX_MAX_INDEXES ; 
 int /*<<< orphan*/  crypto_cleanup_all_ex_data_int (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_new_ex_data_ex (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_ex_data_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_property_parse_init (TYPE_1__*) ; 

__attribute__((used)) static int context_init(OPENSSL_CTX *ctx)
{
    size_t i;
    int exdata_done = 0;

    ctx->lock = CRYPTO_THREAD_lock_new();
    if (ctx->lock == NULL)
        return 0;

    ctx->oncelock = CRYPTO_THREAD_lock_new();
    if (ctx->oncelock == NULL)
        goto err;

    for (i = 0; i < OPENSSL_CTX_MAX_INDEXES; i++) {
        ctx->index_locks[i] = CRYPTO_THREAD_lock_new();
        ctx->dyn_indexes[i] = -1;
        if (ctx->index_locks[i] == NULL)
            goto err;
    }

    /* OPENSSL_CTX is built on top of ex_data so we initialise that directly */
    if (!do_ex_data_init(ctx))
        goto err;
    exdata_done = 1;

    if (!crypto_new_ex_data_ex(ctx, CRYPTO_EX_INDEX_OPENSSL_CTX, NULL,
                               &ctx->data)) {
        crypto_cleanup_all_ex_data_int(ctx);
        goto err;
    }

    /* Everything depends on properties, so we also pre-initialise that */
    if (!ossl_property_parse_init(ctx))
        goto err;

    return 1;
 err:
    if (exdata_done)
        crypto_cleanup_all_ex_data_int(ctx);
    CRYPTO_THREAD_lock_free(ctx->oncelock);
    CRYPTO_THREAD_lock_free(ctx->lock);
    ctx->lock = NULL;
    return 0;
}