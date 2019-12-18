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
struct nn_sinproc {int /*<<< orphan*/  event_connect; int /*<<< orphan*/  fsm; } ;
struct nn_fsm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SINPROC_CONNECT ; 
 int /*<<< orphan*/  NN_SINPROC_SRC_PEER ; 
 int /*<<< orphan*/  nn_fsm_raiseto (int /*<<< orphan*/ *,struct nn_fsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nn_sinproc*) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 

void nn_sinproc_connect (struct nn_sinproc *self, struct nn_fsm *peer)
{
    nn_fsm_start (&self->fsm);

    /*  Start the connecting handshake with the peer. */
    nn_fsm_raiseto (&self->fsm, peer, &self->event_connect,
        NN_SINPROC_SRC_PEER, NN_SINPROC_CONNECT, self);
}