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
struct nn_fq {int /*<<< orphan*/  priolist; } ;

/* Variables and functions */
 int EAGAIN ; 
 int NN_PIPE_RELEASE ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int nn_pipe_recv (struct nn_pipe*,struct nn_msg*) ; 
 int /*<<< orphan*/  nn_priolist_advance (int /*<<< orphan*/ *,int) ; 
 struct nn_pipe* nn_priolist_getpipe (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 

int nn_fq_recv (struct nn_fq *self, struct nn_msg *msg, struct nn_pipe **pipe)
{
    int rc;
    struct nn_pipe *p;

    /*  Pipe is NULL only when there are no avialable pipes. */
    p = nn_priolist_getpipe (&self->priolist);
    if (nn_slow (!p))
        return -EAGAIN;

    /*  Receive the messsage. */
    rc = nn_pipe_recv (p, msg);
    errnum_assert (rc >= 0, -rc);

    /*  Return the pipe data to the user, if required. */
    if (pipe)
        *pipe = p;

    /*  Move to the next pipe. */
    nn_priolist_advance (&self->priolist, rc & NN_PIPE_RELEASE);

    return rc & ~NN_PIPE_RELEASE;
}