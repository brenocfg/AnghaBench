#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct work {void (* member_0 ) (void*) ;void* member_1; } ;
struct mp_thread_pool {scalar_t__ busy_threads; scalar_t__ num_work; scalar_t__ num_threads; scalar_t__ max_threads; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (struct mp_thread_pool*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct work) ; 
 int /*<<< orphan*/  add_thread (struct mp_thread_pool*) ; 
 int /*<<< orphan*/  assert (void (*) (void*)) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool thread_pool_add(struct mp_thread_pool *pool, void (*fn)(void *ctx),
                            void *fn_ctx, bool allow_queue)
{
    bool ok = true;

    assert(fn);

    pthread_mutex_lock(&pool->lock);
    struct work work = {fn, fn_ctx};

    // If there are not enough threads to process all at once, but we can
    // create a new thread, then do so. If work is queued quickly, it can
    // happen that not all available threads have picked up work yet (up to
    // num_threads - busy_threads threads), which has to be accounted for.
    if (pool->busy_threads + pool->num_work + 1 > pool->num_threads &&
        pool->num_threads < pool->max_threads)
    {
        if (!add_thread(pool)) {
            // If we can queue it, it'll get done as long as there is 1 thread.
            ok = allow_queue && pool->num_threads > 0;
        }
    }

    if (ok) {
        MP_TARRAY_INSERT_AT(pool, pool->work, pool->num_work, 0, work);
        pthread_cond_signal(&pool->wakeup);
    }

    pthread_mutex_unlock(&pool->lock);
    return ok;
}