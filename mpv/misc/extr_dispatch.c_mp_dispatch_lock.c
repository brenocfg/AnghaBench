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
struct mp_dispatch_queue {int locked_explicit; int lock_requests; int locked; int /*<<< orphan*/  lock; int /*<<< orphan*/  locked_explicit_thread; int /*<<< orphan*/  cond; scalar_t__ in_process; int /*<<< orphan*/  wakeup_ctx; int /*<<< orphan*/  (* wakeup_fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  in_process_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void mp_dispatch_lock(struct mp_dispatch_queue *queue)
{
    pthread_mutex_lock(&queue->lock);
    // Must not be called recursively from dispatched callbacks.
    if (queue->in_process)
        assert(!pthread_equal(queue->in_process_thread, pthread_self()));
    // Must not be called recursively at all.
    if (queue->locked_explicit)
        assert(!pthread_equal(queue->locked_explicit_thread, pthread_self()));
    queue->lock_requests += 1;
    // And now wait until the target thread gets "trapped" within the
    // mp_dispatch_queue_process() call, which will mean we get exclusive
    // access to the target's thread state.
    while (!queue->in_process) {
        pthread_mutex_unlock(&queue->lock);
        if (queue->wakeup_fn)
            queue->wakeup_fn(queue->wakeup_ctx);
        pthread_mutex_lock(&queue->lock);
        if (queue->in_process)
            break;
        pthread_cond_wait(&queue->cond, &queue->lock);
    }
    // Wait until we can get the lock.
    while (!queue->in_process || queue->locked)
        pthread_cond_wait(&queue->cond, &queue->lock);
    // "Lock".
    assert(queue->lock_requests);
    assert(!queue->locked);
    assert(!queue->locked_explicit);
    queue->locked = true;
    queue->locked_explicit = true;
    queue->locked_explicit_thread = pthread_self();
    pthread_mutex_unlock(&queue->lock);
}