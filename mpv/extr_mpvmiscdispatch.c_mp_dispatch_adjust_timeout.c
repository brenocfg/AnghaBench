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
struct mp_dispatch_queue {scalar_t__ wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; scalar_t__ in_process; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_dispatch_adjust_timeout(struct mp_dispatch_queue *queue, int64_t until)
{
    pthread_mutex_lock(&queue->lock);
    if (queue->in_process && queue->wait > until) {
        queue->wait = until;
        pthread_cond_broadcast(&queue->cond);
    }
    pthread_mutex_unlock(&queue->lock);
}