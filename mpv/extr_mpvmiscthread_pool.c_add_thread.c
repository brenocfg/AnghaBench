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
struct mp_thread_pool {int /*<<< orphan*/  num_threads; int /*<<< orphan*/  threads; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_thread_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mp_thread_pool*) ; 
 int /*<<< orphan*/  worker_thread ; 

__attribute__((used)) static bool add_thread(struct mp_thread_pool *pool)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, worker_thread, pool) != 0)
        return false;

    MP_TARRAY_APPEND(pool, pool->threads, pool->num_threads, thread);
    return true;
}