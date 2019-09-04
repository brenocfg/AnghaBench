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
struct mp_dispatch_queue {int locked; int locked_explicit; int lock_requests; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  locked_explicit_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 

void mp_dispatch_unlock(struct mp_dispatch_queue *queue)
{
    pthread_mutex_lock(&queue->lock);
    assert(queue->locked);
    // Must be called after a mp_dispatch_lock(), from the same thread.
    assert(queue->locked_explicit);
    assert(pthread_equal(queue->locked_explicit_thread, pthread_self()));
    // "Unlock".
    queue->locked = false;
    queue->locked_explicit = false;
    queue->lock_requests -= 1;
    // Wakeup mp_dispatch_queue_process(), and maybe other mp_dispatch_lock()s.
    // (Would be nice to wake up only 1 other locker if lock_requests>0.)
    pthread_cond_broadcast(&queue->cond);
    pthread_mutex_unlock(&queue->lock);
}