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
struct nn_pipe {int dummy; } ;
struct nn_msg {int dummy; } ;
struct nn_lb {int /*<<< orphan*/  priolist; } ;

/* Variables and functions */
 int EAGAIN ; 
 int NN_PIPE_RELEASE ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int nn_pipe_send (struct nn_pipe*,struct nn_msg*) ; 
 int /*<<< orphan*/  nn_priolist_advance (int /*<<< orphan*/ *,int) ; 
 struct nn_pipe* nn_priolist_getpipe (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 

int nn_lb_send (struct nn_lb *self, struct nn_msg *msg, struct nn_pipe **to)
{
    int rc;
    struct nn_pipe *pipe;

    /*  Pipe is NULL only when there are no avialable pipes. */
    pipe = nn_priolist_getpipe (&self->priolist);
    if (nn_slow (!pipe))
        return -EAGAIN;

    /*  Send the messsage. */
    rc = nn_pipe_send (pipe, msg);
    errnum_assert (rc >= 0, -rc);

    /*  Move to the next pipe. */
    nn_priolist_advance (&self->priolist, rc & NN_PIPE_RELEASE);

    if (to != NULL)
        *to = pipe;

    return rc & ~NN_PIPE_RELEASE;
}