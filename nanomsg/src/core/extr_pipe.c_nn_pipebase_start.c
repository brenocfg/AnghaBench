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
struct nn_pipebase {int /*<<< orphan*/  out; int /*<<< orphan*/  fsm; int /*<<< orphan*/  state; int /*<<< orphan*/  sock; int /*<<< orphan*/  outstate; int /*<<< orphan*/  instate; } ;
struct nn_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_PIPEBASE_INSTATE_ASYNC ; 
 int /*<<< orphan*/  NN_PIPEBASE_OUTSTATE_IDLE ; 
 int /*<<< orphan*/  NN_PIPEBASE_STATE_ACTIVE ; 
 int /*<<< orphan*/  NN_PIPEBASE_STATE_FAILED ; 
 int /*<<< orphan*/  NN_PIPEBASE_STATE_IDLE ; 
 int /*<<< orphan*/  NN_PIPE_OUT ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_pipebase*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_sock_add (int /*<<< orphan*/ ,struct nn_pipe*) ; 

int nn_pipebase_start (struct nn_pipebase *self)
{
    int rc;

    nn_assert_state (self, NN_PIPEBASE_STATE_IDLE);

    self->state = NN_PIPEBASE_STATE_ACTIVE;
    self->instate = NN_PIPEBASE_INSTATE_ASYNC;
    self->outstate = NN_PIPEBASE_OUTSTATE_IDLE;
    rc = nn_sock_add (self->sock, (struct nn_pipe*) self);
    if (nn_slow (rc < 0)) {
        self->state = NN_PIPEBASE_STATE_FAILED;
        return rc;
    }
    nn_fsm_raise (&self->fsm, &self->out, NN_PIPE_OUT);

    return 0;
}