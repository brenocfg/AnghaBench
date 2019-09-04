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
struct TYPE_5__ {int* dyn_indexes; int /*<<< orphan*/  lock; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  OPENSSL_CTX_METHOD ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_OPENSSL_CTX ; 
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ CRYPTO_alloc_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* CRYPTO_get_ex_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* default_context ; 
 int /*<<< orphan*/  default_context_init ; 
 int /*<<< orphan*/  do_default_context_init ; 
 int /*<<< orphan*/  openssl_ctx_init_index (TYPE_1__*,int,int /*<<< orphan*/  const*) ; 

void *openssl_ctx_get_data(OPENSSL_CTX *ctx, int index,
                           const OPENSSL_CTX_METHOD *meth)
{
    void *data = NULL;

#ifndef FIPS_MODE
    if (ctx == NULL) {
        if (!RUN_ONCE(&default_context_init, do_default_context_init))
            return NULL;
        ctx = default_context;
    }
#endif
    if (ctx == NULL)
        return NULL;

    CRYPTO_THREAD_read_lock(ctx->lock);

    if (ctx->dyn_indexes[index] == -1
            && !openssl_ctx_init_index(ctx, index, meth)) {
        CRYPTO_THREAD_unlock(ctx->lock);
        return NULL;
    }

    /* The alloc call ensures there's a value there */
    if (CRYPTO_alloc_ex_data(CRYPTO_EX_INDEX_OPENSSL_CTX, NULL,
                             &ctx->data, ctx->dyn_indexes[index]))
        data = CRYPTO_get_ex_data(&ctx->data, ctx->dyn_indexes[index]);

    CRYPTO_THREAD_unlock(ctx->lock);

    return data;
}