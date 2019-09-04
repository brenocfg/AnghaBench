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
struct timespec {int dummy; } ;
struct mp_dispatch_queue {int in_process; int locked; int interrupted; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  cond; int /*<<< orphan*/ * tail; struct mp_dispatch_item* head; scalar_t__ lock_requests; int /*<<< orphan*/  in_process_thread; } ;
struct mp_dispatch_item {int completed; scalar_t__ asynchronous; int /*<<< orphan*/  fn_data; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ) ;struct mp_dispatch_item* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_add_timeout (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  mp_time_us () ; 
 struct timespec mp_time_us_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct mp_dispatch_item*) ; 

void mp_dispatch_queue_process(struct mp_dispatch_queue *queue, double timeout)
{
    pthread_mutex_lock(&queue->lock);
    queue->wait = timeout > 0 ? mp_add_timeout(mp_time_us(), timeout) : 0;
    assert(!queue->in_process); // recursion not allowed
    queue->in_process = true;
    queue->in_process_thread = pthread_self();
    // Wake up thread which called mp_dispatch_lock().
    if (queue->lock_requests)
        pthread_cond_broadcast(&queue->cond);
    while (1) {
        if (queue->lock_requests) {
            // Block due to something having called mp_dispatch_lock().
            pthread_cond_wait(&queue->cond, &queue->lock);
        } else if (queue->head) {
            struct mp_dispatch_item *item = queue->head;
            queue->head = item->next;
            if (!queue->head)
                queue->tail = NULL;
            item->next = NULL;
            // Unlock, because we want to allow other threads to queue items
            // while the dispatch item is processed.
            // At the same time, we must prevent other threads from returning
            // from mp_dispatch_lock(), which is done by locked=true.
            assert(!queue->locked);
            queue->locked = true;
            pthread_mutex_unlock(&queue->lock);

            item->fn(item->fn_data);

            pthread_mutex_lock(&queue->lock);
            assert(queue->locked);
            queue->locked = false;
            // Wakeup mp_dispatch_run(), also mp_dispatch_lock().
            pthread_cond_broadcast(&queue->cond);
            if (item->asynchronous) {
                talloc_free(item);
            } else {
                item->completed = true;
            }
        } else if (queue->wait > 0 && !queue->interrupted) {
            struct timespec ts = mp_time_us_to_timespec(queue->wait);
            if (pthread_cond_timedwait(&queue->cond, &queue->lock, &ts))
                queue->wait = 0;
        } else {
            break;
        }
    }
    assert(!queue->locked);
    queue->in_process = false;
    queue->interrupted = false;
    pthread_mutex_unlock(&queue->lock);
}