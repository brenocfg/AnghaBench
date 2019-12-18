#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nn_sock {TYPE_3__** optsets; int /*<<< orphan*/  ctx; int /*<<< orphan*/  eps; int /*<<< orphan*/  sdeps; int /*<<< orphan*/  relesem; int /*<<< orphan*/  termsem; int /*<<< orphan*/  fsm; int /*<<< orphan*/  sndfd; TYPE_1__* socktype; int /*<<< orphan*/  rcvfd; } ;
struct TYPE_6__ {TYPE_2__* vfptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int EINTR ; 
 int NN_MAX_TRANSPORT ; 
 int NN_SOCKTYPE_FLAG_NORECV ; 
 int NN_SOCKTYPE_FLAG_NOSEND ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_ctx_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ctx_leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ctx_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_efd_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_stopped_noevent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sem_term (int /*<<< orphan*/ *) ; 
 int nn_sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

int nn_sock_term (struct nn_sock *self)
{
    int rc;
    int i;

    /*  NOTE: nn_sock_stop must have already been called. */

    /*  Some endpoints may still be alive.  Here we are going to wait
        till they are all closed.  This loop is not interruptible, because
        making it so would leave a partially cleaned up socket, and we don't
        have a way to defer resource deallocation. */
    for (;;) {
        rc = nn_sem_wait (&self->termsem);
        if (nn_slow (rc == -EINTR))
            continue;
        errnum_assert (rc == 0, -rc);
        break;
    }

    /*  Also, wait for all holds on the socket to be released.  */
    for (;;) {
        rc = nn_sem_wait (&self->relesem);
        if (nn_slow (rc == -EINTR))
            continue;
        errnum_assert (rc == 0, -rc);
        break;
    }

    /*  Threads that posted the semaphore(s) can still have the ctx locked
        for a short while. By simply entering the context and exiting it
        immediately we can be sure that any such threads have already
        exited the context. */
    nn_ctx_enter (&self->ctx);
    nn_ctx_leave (&self->ctx);

    /*  At this point, we can be reasonably certain that no other thread
        has any references to the socket. */

    /*  Close the event FDs entirely. */
    if (!(self->socktype->flags & NN_SOCKTYPE_FLAG_NORECV)) {
        nn_efd_term (&self->rcvfd);
    }
    if (!(self->socktype->flags & NN_SOCKTYPE_FLAG_NOSEND)) {
        nn_efd_term (&self->sndfd);
    }

    nn_fsm_stopped_noevent (&self->fsm);
    nn_fsm_term (&self->fsm);
    nn_sem_term (&self->termsem);
    nn_sem_term (&self->relesem);
    nn_list_term (&self->sdeps);
    nn_list_term (&self->eps);
    nn_ctx_term (&self->ctx);

    /*  Destroy any optsets associated with the socket. */
    for (i = 0; i != NN_MAX_TRANSPORT; ++i)
        if (self->optsets [i])
            self->optsets [i]->vfptr->destroy (self->optsets [i]);

    return 0;
}