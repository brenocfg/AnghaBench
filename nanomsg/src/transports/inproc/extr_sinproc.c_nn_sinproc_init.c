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
struct nn_sinproc {int /*<<< orphan*/  item; int /*<<< orphan*/  event_disconnect; int /*<<< orphan*/  event_received; int /*<<< orphan*/  event_sent; int /*<<< orphan*/  event_connect; int /*<<< orphan*/  msg; int /*<<< orphan*/  msgqueue; int /*<<< orphan*/  pipebase; int /*<<< orphan*/ * peer; scalar_t__ flags; int /*<<< orphan*/  state; int /*<<< orphan*/  fsm; } ;
struct nn_fsm {int dummy; } ;
struct nn_ep {int dummy; } ;
typedef  int /*<<< orphan*/  rcvbuf ;

/* Variables and functions */
 int /*<<< orphan*/  NN_RCVBUF ; 
 int /*<<< orphan*/  NN_SINPROC_STATE_IDLE ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_ep_getopt (struct nn_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nn_sinproc*,struct nn_fsm*) ; 
 int /*<<< orphan*/  nn_list_item_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_msgqueue_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_pipebase_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nn_ep*) ; 
 int /*<<< orphan*/  nn_sinproc_handler ; 
 int /*<<< orphan*/  nn_sinproc_pipebase_vfptr ; 
 int /*<<< orphan*/  nn_sinproc_shutdown ; 

void nn_sinproc_init (struct nn_sinproc *self, int src,
    struct nn_ep *ep, struct nn_fsm *owner)
{
    int rcvbuf;
    size_t sz;

    nn_fsm_init (&self->fsm, nn_sinproc_handler, nn_sinproc_shutdown,
        src, self, owner);
    self->state = NN_SINPROC_STATE_IDLE;
    self->flags = 0;
    self->peer = NULL;
    nn_pipebase_init (&self->pipebase, &nn_sinproc_pipebase_vfptr, ep);
    sz = sizeof (rcvbuf);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_RCVBUF, &rcvbuf, &sz);
    nn_assert (sz == sizeof (rcvbuf));
    nn_msgqueue_init (&self->msgqueue, rcvbuf);
    nn_msg_init (&self->msg, 0);
    nn_fsm_event_init (&self->event_connect);
    nn_fsm_event_init (&self->event_sent);
    nn_fsm_event_init (&self->event_received);
    nn_fsm_event_init (&self->event_disconnect);
    nn_list_item_init (&self->item);
}