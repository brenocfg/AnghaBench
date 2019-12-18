#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nn_usock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  inbuffersz; int /*<<< orphan*/  outbuffersz; int /*<<< orphan*/  sec_attr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fsm; int /*<<< orphan*/  src; } ;
struct nn_aipc {int /*<<< orphan*/  fsm; TYPE_1__ usock; int /*<<< orphan*/  ep; TYPE_2__ listener_owner; struct nn_usock* listener; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_AIPC_SRC_LISTENER ; 
 int /*<<< orphan*/  NN_AIPC_STATE_IDLE ; 
 int /*<<< orphan*/  NN_IPC ; 
 int /*<<< orphan*/  NN_IPC_INBUFSZ ; 
 int /*<<< orphan*/  NN_IPC_OUTBUFSZ ; 
 int /*<<< orphan*/  NN_IPC_SEC_ATTR ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_aipc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ep_getopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_swap_owner (struct nn_usock*,TYPE_2__*) ; 

void nn_aipc_start (struct nn_aipc *self, struct nn_usock *listener)
{
#if defined NN_HAVE_WINDOWS
    size_t sz;
#endif
    nn_assert_state (self, NN_AIPC_STATE_IDLE);

    /*  Take ownership of the listener socket. */
    self->listener = listener;
    self->listener_owner.src = NN_AIPC_SRC_LISTENER;
    self->listener_owner.fsm = &self->fsm;
    nn_usock_swap_owner (listener, &self->listener_owner);

#if defined NN_HAVE_WINDOWS
    /* Get/Set security attribute pointer*/
    nn_ep_getopt (self->ep, NN_IPC, NN_IPC_SEC_ATTR, &self->usock.sec_attr, &sz);
    nn_ep_getopt (self->ep, NN_IPC, NN_IPC_OUTBUFSZ, &self->usock.outbuffersz, &sz);
    nn_ep_getopt (self->ep, NN_IPC, NN_IPC_INBUFSZ, &self->usock.inbuffersz, &sz);
#endif

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);
}