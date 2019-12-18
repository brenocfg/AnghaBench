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
typedef  int uint64_t ;
struct nn_sock {int sndtimeo; int state; int /*<<< orphan*/  flags; int /*<<< orphan*/  sndfd; int /*<<< orphan*/  ctx; TYPE_3__* sockbase; TYPE_1__* socktype; } ;
struct nn_msg {int dummy; } ;
struct TYPE_6__ {TYPE_2__* vfptr; } ;
struct TYPE_5__ {int (* send ) (TYPE_3__*,struct nn_msg*) ;} ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADF ; 
 int EINTR ; 
 int ENOTSUP ; 
 int ETIMEDOUT ; 
 int NN_DONTWAIT ; 
 int NN_SOCKTYPE_FLAG_NOSEND ; 
 int /*<<< orphan*/  NN_SOCK_FLAG_OUT ; 
#define  NN_SOCK_STATE_ACTIVE 132 
#define  NN_SOCK_STATE_FINI 131 
#define  NN_SOCK_STATE_INIT 130 
#define  NN_SOCK_STATE_STOPPING 129 
#define  NN_SOCK_STATE_STOPPING_EPS 128 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_clock_ms () ; 
 int /*<<< orphan*/  nn_ctx_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ctx_leave (int /*<<< orphan*/ *) ; 
 int nn_efd_wait (int /*<<< orphan*/ *,int) ; 
 scalar_t__ nn_fast (int) ; 
 scalar_t__ nn_slow (int) ; 
 int stub1 (TYPE_3__*,struct nn_msg*) ; 

int nn_sock_send (struct nn_sock *self, struct nn_msg *msg, int flags)
{
    int rc;
    uint64_t deadline;
    uint64_t now;
    int timeout;

    /*  Some sockets types cannot be used for sending messages. */
    if (nn_slow (self->socktype->flags & NN_SOCKTYPE_FLAG_NOSEND))
        return -ENOTSUP;

    nn_ctx_enter (&self->ctx);

    /*  Compute the deadline for SNDTIMEO timer. */
    if (self->sndtimeo < 0) {
        deadline = -1;
        timeout = -1;
    }
    else {
        deadline = nn_clock_ms() + self->sndtimeo;
        timeout = self->sndtimeo;
    }

    while (1) {

        switch (self->state) {
        case NN_SOCK_STATE_ACTIVE:
        case NN_SOCK_STATE_INIT:
             break;

        case NN_SOCK_STATE_STOPPING_EPS:
        case NN_SOCK_STATE_STOPPING:
        case NN_SOCK_STATE_FINI:
            /*  Socket closed or closing.  Should we return something
                else here; recvmsg(2) for example returns no data in
                this case, like read(2).  The use of indexed file
                descriptors is further problematic, as an FD can be reused
                leading to situations where technically the outstanding
                operation should refer to some other socket entirely.  */
            nn_ctx_leave (&self->ctx);
            return -EBADF;
        }

        /*  Try to send the message in a non-blocking way. */
        rc = self->sockbase->vfptr->send (self->sockbase, msg);
        if (nn_fast (rc == 0)) {
            nn_ctx_leave (&self->ctx);
            return 0;
        }
        nn_assert (rc < 0);

        /*  Any unexpected error is forwarded to the caller. */
        if (nn_slow (rc != -EAGAIN)) {
            nn_ctx_leave (&self->ctx);
            return rc;
        }

        /*  If the message cannot be sent at the moment and the send call
            is non-blocking, return immediately. */
        if (nn_fast (flags & NN_DONTWAIT)) {
            nn_ctx_leave (&self->ctx);
            return -EAGAIN;
        }

        /*  With blocking send, wait while there are new pipes available
            for sending. */
        nn_ctx_leave (&self->ctx);
        rc = nn_efd_wait (&self->sndfd, timeout);
        if (nn_slow (rc == -ETIMEDOUT))
            return -ETIMEDOUT;
        if (nn_slow (rc == -EINTR))
            return -EINTR;
        if (nn_slow (rc == -EBADF))
            return -EBADF;
        errnum_assert (rc == 0, rc);
        nn_ctx_enter (&self->ctx);
        /*
         *  Double check if pipes are still available for sending
         */
        if (!nn_efd_wait (&self->sndfd, 0)) {
            self->flags |= NN_SOCK_FLAG_OUT;
        }

        /*  If needed, re-compute the timeout to reflect the time that have
            already elapsed. */
        if (self->sndtimeo >= 0) {
            now = nn_clock_ms();
            timeout = (int) (now > deadline ? 0 : deadline - now);
        }
    }
}