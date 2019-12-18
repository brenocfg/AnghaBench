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
struct nn_pipebase {scalar_t__ outstate; int /*<<< orphan*/  out; int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 scalar_t__ NN_PIPEBASE_OUTSTATE_ASYNC ; 
 scalar_t__ NN_PIPEBASE_OUTSTATE_IDLE ; 
 scalar_t__ NN_PIPEBASE_OUTSTATE_SENDING ; 
 scalar_t__ NN_PIPEBASE_OUTSTATE_SENT ; 
 int /*<<< orphan*/  NN_PIPE_OUT ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_fast (int) ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nn_pipebase_sent (struct nn_pipebase *self)
{
    if (nn_fast (self->outstate == NN_PIPEBASE_OUTSTATE_SENDING)) {
        self->outstate = NN_PIPEBASE_OUTSTATE_SENT;
        return;
    }
    nn_assert (self->outstate == NN_PIPEBASE_OUTSTATE_ASYNC);
    self->outstate = NN_PIPEBASE_OUTSTATE_IDLE;
    nn_fsm_raise (&self->fsm, &self->out, NN_PIPE_OUT);
}