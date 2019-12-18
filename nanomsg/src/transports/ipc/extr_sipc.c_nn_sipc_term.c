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
struct nn_sipc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  streamhdr; int /*<<< orphan*/  pipebase; int /*<<< orphan*/  inmsg; int /*<<< orphan*/  outmsg; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SIPC_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_sipc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_pipebase_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_streamhdr_term (int /*<<< orphan*/ *) ; 

void nn_sipc_term (struct nn_sipc *self)
{
    nn_assert_state (self, NN_SIPC_STATE_IDLE);

    nn_fsm_event_term (&self->done);
    nn_msg_term (&self->outmsg);
    nn_msg_term (&self->inmsg);
    nn_pipebase_term (&self->pipebase);
    nn_streamhdr_term (&self->streamhdr);
    nn_fsm_term (&self->fsm);
}