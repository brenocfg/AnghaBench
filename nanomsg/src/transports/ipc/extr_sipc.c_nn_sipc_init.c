#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int src; int /*<<< orphan*/ * fsm; } ;
struct nn_sipc {int instate; int outstate; int /*<<< orphan*/  done; int /*<<< orphan*/  outmsg; int /*<<< orphan*/  inmsg; int /*<<< orphan*/  pipebase; TYPE_1__ usock_owner; int /*<<< orphan*/ * usock; int /*<<< orphan*/  fsm; int /*<<< orphan*/  streamhdr; int /*<<< orphan*/  state; } ;
struct nn_fsm {int dummy; } ;
struct nn_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SIPC_SRC_STREAMHDR ; 
 int /*<<< orphan*/  NN_SIPC_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nn_sipc*,struct nn_fsm*) ; 
 int /*<<< orphan*/  nn_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_pipebase_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nn_ep*) ; 
 int /*<<< orphan*/  nn_sipc_handler ; 
 int /*<<< orphan*/  nn_sipc_pipebase_vfptr ; 
 int /*<<< orphan*/  nn_sipc_shutdown ; 
 int /*<<< orphan*/  nn_streamhdr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_sipc_init (struct nn_sipc *self, int src,
    struct nn_ep *ep, struct nn_fsm *owner)
{
    nn_fsm_init (&self->fsm, nn_sipc_handler, nn_sipc_shutdown,
        src, self, owner);
    self->state = NN_SIPC_STATE_IDLE;
    nn_streamhdr_init (&self->streamhdr, NN_SIPC_SRC_STREAMHDR, &self->fsm);
    self->usock = NULL;
    self->usock_owner.src = -1;
    self->usock_owner.fsm = NULL;
    nn_pipebase_init (&self->pipebase, &nn_sipc_pipebase_vfptr, ep);
    self->instate = -1;
    nn_msg_init (&self->inmsg, 0);
    self->outstate = -1;
    nn_msg_init (&self->outmsg, 0);
    nn_fsm_event_init (&self->done);
}