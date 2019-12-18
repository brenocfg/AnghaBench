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
struct nn_sock {TYPE_2__* sockbase; } ;
struct nn_pipe {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vfptr; } ;
struct TYPE_3__ {int (* add ) (TYPE_2__*,struct nn_pipe*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NN_STAT_CURRENT_CONNECTIONS ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_sock_stat_increment (struct nn_sock*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,struct nn_pipe*) ; 

int nn_sock_add (struct nn_sock *self, struct nn_pipe *pipe)
{
    int rc;

    rc = self->sockbase->vfptr->add (self->sockbase, pipe);
    if (nn_slow (rc >= 0)) {
        nn_sock_stat_increment (self, NN_STAT_CURRENT_CONNECTIONS, 1);
    }
    return rc;
}