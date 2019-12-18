#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t max_size; size_t curr_size; int /*<<< orphan*/ * jobs; } ;
typedef  TYPE_1__ async_pool ;
struct TYPE_11__ {int /*<<< orphan*/ * funcargs; int /*<<< orphan*/  fibrectx; } ;
typedef  TYPE_2__ ASYNC_JOB ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_F_ASYNC_INIT_THREAD ; 
 int /*<<< orphan*/  ASYNC_R_FAILED_TO_SET_POOL ; 
 int /*<<< orphan*/  ASYNC_R_INVALID_POOL_SIZE ; 
 int /*<<< orphan*/  ASYNCerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_INIT_ASYNC ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  async_delete_thread_state ; 
 int /*<<< orphan*/  async_empty_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  async_fibre_makecontext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_job_free (TYPE_2__*) ; 
 TYPE_2__* async_job_new () ; 
 int /*<<< orphan*/  ossl_init_thread_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poolkey ; 
 int /*<<< orphan*/  sk_ASYNC_JOB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_ASYNC_JOB_new_reserve (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sk_ASYNC_JOB_push (int /*<<< orphan*/ *,TYPE_2__*) ; 

int ASYNC_init_thread(size_t max_size, size_t init_size)
{
    async_pool *pool;
    size_t curr_size = 0;

    if (init_size > max_size) {
        ASYNCerr(ASYNC_F_ASYNC_INIT_THREAD, ASYNC_R_INVALID_POOL_SIZE);
        return 0;
    }

    if (!OPENSSL_init_crypto(OPENSSL_INIT_ASYNC, NULL))
        return 0;

    if (!ossl_init_thread_start(NULL, NULL, async_delete_thread_state))
        return 0;

    pool = OPENSSL_zalloc(sizeof(*pool));
    if (pool == NULL) {
        ASYNCerr(ASYNC_F_ASYNC_INIT_THREAD, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    pool->jobs = sk_ASYNC_JOB_new_reserve(NULL, init_size);
    if (pool->jobs == NULL) {
        ASYNCerr(ASYNC_F_ASYNC_INIT_THREAD, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(pool);
        return 0;
    }

    pool->max_size = max_size;

    /* Pre-create jobs as required */
    while (init_size--) {
        ASYNC_JOB *job;
        job = async_job_new();
        if (job == NULL || !async_fibre_makecontext(&job->fibrectx)) {
            /*
             * Not actually fatal because we already created the pool, just
             * skip creation of any more jobs
             */
            async_job_free(job);
            break;
        }
        job->funcargs = NULL;
        sk_ASYNC_JOB_push(pool->jobs, job); /* Cannot fail due to reserve */
        curr_size++;
    }
    pool->curr_size = curr_size;
    if (!CRYPTO_THREAD_set_local(&poolkey, pool)) {
        ASYNCerr(ASYNC_F_ASYNC_INIT_THREAD, ASYNC_R_FAILED_TO_SET_POOL);
        goto err;
    }

    return 1;
err:
    async_empty_pool(pool);
    sk_ASYNC_JOB_free(pool->jobs);
    OPENSSL_free(pool);
    return 0;
}