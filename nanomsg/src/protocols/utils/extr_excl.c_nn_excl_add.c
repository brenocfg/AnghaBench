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
struct nn_excl {struct nn_pipe* pipe; } ;

/* Variables and functions */
 int EISCONN ; 

int nn_excl_add (struct nn_excl *self, struct nn_pipe *pipe)
{
    /*  If there's a connection being used, reject any new connection. */
    if (self->pipe)
        return -EISCONN;

    /*  Remember that this pipe is the active one. */
    self->pipe = pipe;

    return 0;
}