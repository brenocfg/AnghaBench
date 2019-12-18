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
struct nn_pipebase {scalar_t__ state; int /*<<< orphan*/  sock; } ;
struct nn_pipe {int dummy; } ;

/* Variables and functions */
 scalar_t__ NN_PIPEBASE_STATE_ACTIVE ; 
 scalar_t__ NN_PIPEBASE_STATE_IDLE ; 
 int /*<<< orphan*/  nn_sock_rm (int /*<<< orphan*/ ,struct nn_pipe*) ; 

void nn_pipebase_stop (struct nn_pipebase *self)
{
    if (self->state == NN_PIPEBASE_STATE_ACTIVE)
        nn_sock_rm (self->sock, (struct nn_pipe*) self);
    self->state = NN_PIPEBASE_STATE_IDLE;
}