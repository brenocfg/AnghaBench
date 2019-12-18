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
struct nn_ws_handshake {int /*<<< orphan*/  done; int /*<<< orphan*/  fsm; int /*<<< orphan*/  state; TYPE_1__ usock_owner; int /*<<< orphan*/ * usock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_WS_HANDSHAKE_STATE_DONE ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_usock_swap_owner (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void nn_ws_handshake_leave (struct nn_ws_handshake *self, int rc)
{
    nn_usock_swap_owner (self->usock, &self->usock_owner);
    self->usock = NULL;
    self->usock_owner.src = -1;
    self->usock_owner.fsm = NULL;
    self->state = NN_WS_HANDSHAKE_STATE_DONE;
    nn_fsm_raise (&self->fsm, &self->done, rc);
}