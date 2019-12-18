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
typedef  int (* openssl_ctx_run_once_fn ) (TYPE_1__*) ;
struct TYPE_7__ {int* run_once_done; int* run_once_ret; int /*<<< orphan*/  oncelock; } ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 TYPE_1__* openssl_ctx_get_concrete (TYPE_1__*) ; 

int openssl_ctx_run_once(OPENSSL_CTX *ctx, unsigned int idx,
                         openssl_ctx_run_once_fn run_once_fn)
{
    int done = 0, ret = 0;

    ctx = openssl_ctx_get_concrete(ctx);
    if (ctx == NULL)
        return 0;

    CRYPTO_THREAD_read_lock(ctx->oncelock);
    done = ctx->run_once_done[idx];
    if (done)
        ret = ctx->run_once_ret[idx];
    CRYPTO_THREAD_unlock(ctx->oncelock);

    if (done)
        return ret;

    CRYPTO_THREAD_write_lock(ctx->oncelock);
    if (ctx->run_once_done[idx]) {
        ret = ctx->run_once_ret[idx];
        CRYPTO_THREAD_unlock(ctx->oncelock);
        return ret;
    }

    ret = run_once_fn(ctx);
    ctx->run_once_done[idx] = 1;
    ctx->run_once_ret[idx] = ret;
    CRYPTO_THREAD_unlock(ctx->oncelock);

    return ret;
}