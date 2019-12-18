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
struct nn_aipc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  sipc; int /*<<< orphan*/  accepted; int /*<<< orphan*/  done; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_AIPC_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_aipc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_item_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sipc_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_term (int /*<<< orphan*/ *) ; 

void nn_aipc_term (struct nn_aipc *self)
{
    nn_assert_state (self, NN_AIPC_STATE_IDLE);

    nn_list_item_term (&self->item);
    nn_fsm_event_term (&self->done);
    nn_fsm_event_term (&self->accepted);
    nn_sipc_term (&self->sipc);
    nn_usock_term (&self->usock);
    nn_fsm_term (&self->fsm);
}