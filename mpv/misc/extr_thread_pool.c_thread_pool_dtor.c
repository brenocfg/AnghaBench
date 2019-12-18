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
struct mp_thread_pool {int terminate; int num_threads; scalar_t__ num_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/ * threads; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thread_pool_dtor(void *ctx)
{
    struct mp_thread_pool *pool = ctx;


    pthread_mutex_lock(&pool->lock);

    pool->terminate = true;
    pthread_cond_broadcast(&pool->wakeup);

    pthread_t *threads = pool->threads;
    int num_threads = pool->num_threads;

    pool->threads = NULL;
    pool->num_threads = 0;

    pthread_mutex_unlock(&pool->lock);

    for (int n = 0; n < num_threads; n++)
        pthread_join(threads[n], NULL);

    assert(pool->num_work == 0);
    assert(pool->num_threads == 0);
    pthread_cond_destroy(&pool->wakeup);
    pthread_mutex_destroy(&pool->lock);
}