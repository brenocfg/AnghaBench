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
struct nn_sinproc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  pipebase; int /*<<< orphan*/  msgqueue; int /*<<< orphan*/  msg; int /*<<< orphan*/  event_connect; int /*<<< orphan*/  event_sent; int /*<<< orphan*/  event_received; int /*<<< orphan*/  event_disconnect; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_item_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msgqueue_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_pipebase_term (int /*<<< orphan*/ *) ; 

void nn_sinproc_term (struct nn_sinproc *self)
{
    nn_list_item_term (&self->item);
    nn_fsm_event_term (&self->event_disconnect);
    nn_fsm_event_term (&self->event_received);
    nn_fsm_event_term (&self->event_sent);
    nn_fsm_event_term (&self->event_connect);
    nn_msg_term (&self->msg);
    nn_msgqueue_term (&self->msgqueue);
    nn_pipebase_term (&self->pipebase);
    nn_fsm_term (&self->fsm);
}