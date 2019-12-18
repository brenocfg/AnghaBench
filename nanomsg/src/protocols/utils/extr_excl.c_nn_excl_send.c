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
struct nn_msg {int dummy; } ;
struct nn_excl {int /*<<< orphan*/ * outpipe; } ;

/* Variables and functions */
 int EAGAIN ; 
 int NN_PIPE_RELEASE ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int nn_pipe_send (int /*<<< orphan*/ *,struct nn_msg*) ; 
 scalar_t__ nn_slow (int) ; 

int nn_excl_send (struct nn_excl *self, struct nn_msg *msg)
{
    int rc;

    if (nn_slow (!self->outpipe))
        return -EAGAIN;

    rc = nn_pipe_send (self->outpipe, msg);
    errnum_assert (rc >= 0, -rc);

    if (rc & NN_PIPE_RELEASE)
        self->outpipe = NULL;

    return rc & ~NN_PIPE_RELEASE;
}