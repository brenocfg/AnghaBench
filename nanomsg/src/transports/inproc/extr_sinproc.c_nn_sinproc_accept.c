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
struct nn_sinproc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  event_connect; struct nn_sinproc* peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SINPROC_ACTION_READY ; 
 int /*<<< orphan*/  NN_SINPROC_READY ; 
 int /*<<< orphan*/  NN_SINPROC_SRC_PEER ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_fsm_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_raiseto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nn_sinproc*) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 

void nn_sinproc_accept (struct nn_sinproc *self, struct nn_sinproc *peer)
{
    nn_assert (!self->peer);
    self->peer = peer;

    /*  Start the connecting handshake with the peer. */
    nn_fsm_raiseto (&self->fsm, &peer->fsm, &self->event_connect,
        NN_SINPROC_SRC_PEER, NN_SINPROC_READY, self);

    /*  Notify the state machine. */
    nn_fsm_start (&self->fsm);
    nn_fsm_action (&self->fsm, NN_SINPROC_ACTION_READY);
}