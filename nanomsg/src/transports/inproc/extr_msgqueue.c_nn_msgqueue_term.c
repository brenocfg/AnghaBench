#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ chunk; } ;
struct TYPE_3__ {scalar_t__ chunk; } ;
struct nn_msgqueue {scalar_t__ cache; TYPE_2__ in; TYPE_1__ out; } ;
struct nn_msg {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_free (scalar_t__) ; 
 int /*<<< orphan*/  nn_msg_term (struct nn_msg*) ; 
 int nn_msgqueue_recv (struct nn_msgqueue*,struct nn_msg*) ; 

void nn_msgqueue_term (struct nn_msgqueue *self)
{
    int rc;
    struct nn_msg msg;

    /*  Deallocate messages in the pipe. */
    while (1) {
        rc = nn_msgqueue_recv (self, &msg);
        if (rc == -EAGAIN)
            break;
        errnum_assert (rc >= 0, -rc);
        nn_msg_term (&msg);
    }

    /*  There are no more messages in the pipe so there's at most one chunk
        in the queue. Deallocate it. */
    nn_assert (self->in.chunk == self->out.chunk);
    nn_free (self->in.chunk);

    /*  Deallocate the cached chunk, if any. */
    if (self->cache)
        nn_free (self->cache);
}