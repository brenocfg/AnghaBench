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
struct nn_pipebase {int /*<<< orphan*/  fsm; int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_PIPEBASE_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_pipebase*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 

void nn_pipebase_term (struct nn_pipebase *self)
{
    nn_assert_state (self, NN_PIPEBASE_STATE_IDLE);

    nn_fsm_event_term (&self->out);
    nn_fsm_event_term (&self->in);
    nn_fsm_term (&self->fsm);
}