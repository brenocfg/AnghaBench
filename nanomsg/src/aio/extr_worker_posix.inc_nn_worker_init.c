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
struct nn_worker {int /*<<< orphan*/  thread; int /*<<< orphan*/  timerset; int /*<<< orphan*/  efd_hndl; int /*<<< orphan*/  poller; int /*<<< orphan*/  efd; int /*<<< orphan*/  stop; int /*<<< orphan*/  tasks; int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_efd_getfd (int /*<<< orphan*/ *) ; 
 int nn_efd_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_poller_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_poller_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_poller_set_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_queue_item_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_thread_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nn_worker*) ; 
 int /*<<< orphan*/  nn_timerset_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_routine ; 

int nn_worker_init (struct nn_worker *self)
{
    int rc;

    rc = nn_efd_init (&self->efd);
    if (rc < 0)
        return rc;

    nn_mutex_init (&self->sync);
    nn_queue_init (&self->tasks);
    nn_queue_item_init (&self->stop);
    nn_poller_init (&self->poller);
    nn_poller_add (&self->poller, nn_efd_getfd (&self->efd), &self->efd_hndl);
    nn_poller_set_in (&self->poller, &self->efd_hndl);
    nn_timerset_init (&self->timerset);
    nn_thread_init (&self->thread, nn_worker_routine, self);

    return 0;
}