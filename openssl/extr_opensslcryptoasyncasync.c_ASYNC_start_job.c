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
struct TYPE_8__ {TYPE_2__* currjob; int /*<<< orphan*/  dispatcher; } ;
typedef  TYPE_1__ async_ctx ;
struct TYPE_9__ {scalar_t__ status; int ret; int (* func ) (void*) ;int /*<<< orphan*/  fibrectx; int /*<<< orphan*/ * waitctx; int /*<<< orphan*/ * funcargs; } ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;
typedef  TYPE_2__ ASYNC_JOB ;

/* Variables and functions */
 int ASYNC_ERR ; 
 int ASYNC_FINISH ; 
 int /*<<< orphan*/  ASYNC_F_ASYNC_START_JOB ; 
 scalar_t__ ASYNC_JOB_PAUSED ; 
 scalar_t__ ASYNC_JOB_PAUSING ; 
 scalar_t__ ASYNC_JOB_STOPPING ; 
 int ASYNC_NO_JOBS ; 
 int ASYNC_PAUSE ; 
 int /*<<< orphan*/  ASYNC_R_FAILED_TO_SWAP_CONTEXT ; 
 int /*<<< orphan*/  ASYNCerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_INIT_ASYNC ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (size_t) ; 
 TYPE_1__* async_ctx_new () ; 
 int /*<<< orphan*/  async_fibre_swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* async_get_ctx () ; 
 TYPE_2__* async_get_pool_job () ; 
 int /*<<< orphan*/  async_release_job (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 

int ASYNC_start_job(ASYNC_JOB **job, ASYNC_WAIT_CTX *wctx, int *ret,
                    int (*func)(void *), void *args, size_t size)
{
    async_ctx *ctx;

    if (!OPENSSL_init_crypto(OPENSSL_INIT_ASYNC, NULL))
        return ASYNC_ERR;

    ctx = async_get_ctx();
    if (ctx == NULL)
        ctx = async_ctx_new();
    if (ctx == NULL)
        return ASYNC_ERR;

    if (*job)
        ctx->currjob = *job;

    for (;;) {
        if (ctx->currjob != NULL) {
            if (ctx->currjob->status == ASYNC_JOB_STOPPING) {
                *ret = ctx->currjob->ret;
                ctx->currjob->waitctx = NULL;
                async_release_job(ctx->currjob);
                ctx->currjob = NULL;
                *job = NULL;
                return ASYNC_FINISH;
            }

            if (ctx->currjob->status == ASYNC_JOB_PAUSING) {
                *job = ctx->currjob;
                ctx->currjob->status = ASYNC_JOB_PAUSED;
                ctx->currjob = NULL;
                return ASYNC_PAUSE;
            }

            if (ctx->currjob->status == ASYNC_JOB_PAUSED) {
                ctx->currjob = *job;
                /* Resume previous job */
                if (!async_fibre_swapcontext(&ctx->dispatcher,
                        &ctx->currjob->fibrectx, 1)) {
                    ASYNCerr(ASYNC_F_ASYNC_START_JOB,
                             ASYNC_R_FAILED_TO_SWAP_CONTEXT);
                    goto err;
                }
                continue;
            }

            /* Should not happen */
            ASYNCerr(ASYNC_F_ASYNC_START_JOB, ERR_R_INTERNAL_ERROR);
            async_release_job(ctx->currjob);
            ctx->currjob = NULL;
            *job = NULL;
            return ASYNC_ERR;
        }

        /* Start a new job */
        if ((ctx->currjob = async_get_pool_job()) == NULL)
            return ASYNC_NO_JOBS;

        if (args != NULL) {
            ctx->currjob->funcargs = OPENSSL_malloc(size);
            if (ctx->currjob->funcargs == NULL) {
                ASYNCerr(ASYNC_F_ASYNC_START_JOB, ERR_R_MALLOC_FAILURE);
                async_release_job(ctx->currjob);
                ctx->currjob = NULL;
                return ASYNC_ERR;
            }
            memcpy(ctx->currjob->funcargs, args, size);
        } else {
            ctx->currjob->funcargs = NULL;
        }

        ctx->currjob->func = func;
        ctx->currjob->waitctx = wctx;
        if (!async_fibre_swapcontext(&ctx->dispatcher,
                &ctx->currjob->fibrectx, 1)) {
            ASYNCerr(ASYNC_F_ASYNC_START_JOB, ASYNC_R_FAILED_TO_SWAP_CONTEXT);
            goto err;
        }
    }

err:
    async_release_job(ctx->currjob);
    ctx->currjob = NULL;
    *job = NULL;
    return ASYNC_ERR;
}