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
struct openssl_ctx_onfree_list_st {struct openssl_ctx_onfree_list_st* next; int /*<<< orphan*/  (* fn ) (TYPE_1__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/ * oncelock; int /*<<< orphan*/ ** index_locks; int /*<<< orphan*/  data; struct openssl_ctx_onfree_list_st* onfreelist; } ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_OPENSSL_CTX ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int OPENSSL_CTX_MAX_INDEXES ; 
 int /*<<< orphan*/  OPENSSL_free (struct openssl_ctx_onfree_list_st*) ; 
 int /*<<< orphan*/  crypto_cleanup_all_ex_data_int (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_ctx_thread_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int context_deinit(OPENSSL_CTX *ctx)
{
    struct openssl_ctx_onfree_list_st *tmp, *onfree;
    int i;

    if (ctx == NULL)
        return 1;

    ossl_ctx_thread_stop(ctx);

    onfree = ctx->onfreelist;
    while (onfree != NULL) {
        onfree->fn(ctx);
        tmp = onfree;
        onfree = onfree->next;
        OPENSSL_free(tmp);
    }
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_OPENSSL_CTX, NULL, &ctx->data);
    crypto_cleanup_all_ex_data_int(ctx);
    for (i = 0; i < OPENSSL_CTX_MAX_INDEXES; i++)
        CRYPTO_THREAD_lock_free(ctx->index_locks[i]);

    CRYPTO_THREAD_lock_free(ctx->oncelock);
    CRYPTO_THREAD_lock_free(ctx->lock);
    ctx->lock = NULL;
    return 1;
}