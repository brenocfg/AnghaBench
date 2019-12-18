#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* dyn_indexes; int /*<<< orphan*/ * index_locks; int /*<<< orphan*/  data; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  OPENSSL_CTX_METHOD ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_OPENSSL_CTX ; 
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ CRYPTO_alloc_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* CRYPTO_get_ex_data (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* openssl_ctx_get_concrete (TYPE_1__*) ; 
 int /*<<< orphan*/  openssl_ctx_init_index (TYPE_1__*,int,int /*<<< orphan*/  const*) ; 

void *openssl_ctx_get_data(OPENSSL_CTX *ctx, int index,
                           const OPENSSL_CTX_METHOD *meth)
{
    void *data = NULL;
    int dynidx;

    ctx = openssl_ctx_get_concrete(ctx);
    if (ctx == NULL)
        return NULL;

    CRYPTO_THREAD_read_lock(ctx->lock);
    dynidx = ctx->dyn_indexes[index];
    CRYPTO_THREAD_unlock(ctx->lock);

    if (dynidx != -1) {
        CRYPTO_THREAD_read_lock(ctx->index_locks[index]);
        data = CRYPTO_get_ex_data(&ctx->data, dynidx);
        CRYPTO_THREAD_unlock(ctx->index_locks[index]);
        return data;
    }

    CRYPTO_THREAD_write_lock(ctx->index_locks[index]);
    CRYPTO_THREAD_write_lock(ctx->lock);

    dynidx = ctx->dyn_indexes[index];
    if (dynidx != -1) {
        CRYPTO_THREAD_unlock(ctx->lock);
        data = CRYPTO_get_ex_data(&ctx->data, dynidx);
        CRYPTO_THREAD_unlock(ctx->index_locks[index]);
        return data;
    }

    if (!openssl_ctx_init_index(ctx, index, meth)) {
        CRYPTO_THREAD_unlock(ctx->lock);
        CRYPTO_THREAD_unlock(ctx->index_locks[index]);
        return NULL;
    }

    CRYPTO_THREAD_unlock(ctx->lock);

    /* The alloc call ensures there's a value there */
    if (CRYPTO_alloc_ex_data(CRYPTO_EX_INDEX_OPENSSL_CTX, NULL,
                             &ctx->data, ctx->dyn_indexes[index]))
        data = CRYPTO_get_ex_data(&ctx->data, ctx->dyn_indexes[index]);

    CRYPTO_THREAD_unlock(ctx->index_locks[index]);

    return data;
}