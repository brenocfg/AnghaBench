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
struct nn_worker {int /*<<< orphan*/  sync; int /*<<< orphan*/  tasks; int /*<<< orphan*/  stop; int /*<<< orphan*/  efd; int /*<<< orphan*/  poller; int /*<<< orphan*/  timerset; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_efd_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_efd_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_poller_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_queue_item_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_queue_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_queue_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_timerset_term (int /*<<< orphan*/ *) ; 

void nn_worker_term (struct nn_worker *self)
{
    /*  Ask worker thread to terminate. */
    nn_mutex_lock (&self->sync);
    nn_queue_push (&self->tasks, &self->stop);
    nn_efd_signal (&self->efd);
    nn_mutex_unlock (&self->sync);

    /*  Wait till worker thread terminates. */
    nn_thread_term (&self->thread);

    /*  Clean up. */
    nn_timerset_term (&self->timerset);
    nn_poller_term (&self->poller);
    nn_efd_term (&self->efd);
    nn_queue_item_term (&self->stop);
    nn_queue_term (&self->tasks);
    nn_mutex_term (&self->sync);
}