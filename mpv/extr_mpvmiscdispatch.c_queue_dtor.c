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
struct mp_dispatch_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  locked; int /*<<< orphan*/  lock_requests; int /*<<< orphan*/  in_process; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_dtor(void *p)
{
    struct mp_dispatch_queue *queue = p;
    assert(!queue->head);
    assert(!queue->in_process);
    assert(!queue->lock_requests);
    assert(!queue->locked);
    pthread_cond_destroy(&queue->cond);
    pthread_mutex_destroy(&queue->lock);
}