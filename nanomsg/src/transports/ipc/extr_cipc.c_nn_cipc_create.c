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
struct nn_ep {int dummy; } ;
struct nn_cipc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  sipc; int /*<<< orphan*/  retry; int /*<<< orphan*/  usock; int /*<<< orphan*/  state; struct nn_ep* ep; } ;
typedef  int /*<<< orphan*/  reconnect_ivl_max ;
typedef  int /*<<< orphan*/  reconnect_ivl ;

/* Variables and functions */
 int /*<<< orphan*/  NN_CIPC_SRC_RECONNECT_TIMER ; 
 int /*<<< orphan*/  NN_CIPC_SRC_SIPC ; 
 int /*<<< orphan*/  NN_CIPC_SRC_USOCK ; 
 int /*<<< orphan*/  NN_CIPC_STATE_IDLE ; 
 int /*<<< orphan*/  NN_RECONNECT_IVL ; 
 int /*<<< orphan*/  NN_RECONNECT_IVL_MAX ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  alloc_assert (struct nn_cipc*) ; 
 struct nn_cipc* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_backoff_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_cipc_ep_ops ; 
 int /*<<< orphan*/  nn_cipc_handler ; 
 int /*<<< orphan*/  nn_cipc_shutdown ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getopt (struct nn_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_cipc*) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sipc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nn_ep*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nn_cipc_create (struct nn_ep *ep)
{
    struct nn_cipc *self;
    int reconnect_ivl;
    int reconnect_ivl_max;
    size_t sz;

    /*  Allocate the new endpoint object. */
    self = nn_alloc (sizeof (struct nn_cipc), "cipc");
    alloc_assert (self);

    /*  Initialise the structure. */
    self->ep = ep;
    nn_ep_tran_setup (ep, &nn_cipc_ep_ops, self);
    nn_fsm_init_root (&self->fsm, nn_cipc_handler, nn_cipc_shutdown,
        nn_ep_getctx (ep));
    self->state = NN_CIPC_STATE_IDLE;
    nn_usock_init (&self->usock, NN_CIPC_SRC_USOCK, &self->fsm);
    sz = sizeof (reconnect_ivl);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_RECONNECT_IVL, &reconnect_ivl, &sz);
    nn_assert (sz == sizeof (reconnect_ivl));
    sz = sizeof (reconnect_ivl_max);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_RECONNECT_IVL_MAX,
        &reconnect_ivl_max, &sz);
    nn_assert (sz == sizeof (reconnect_ivl_max));
    if (reconnect_ivl_max == 0)
        reconnect_ivl_max = reconnect_ivl;
    nn_backoff_init (&self->retry, NN_CIPC_SRC_RECONNECT_TIMER,
        reconnect_ivl, reconnect_ivl_max, &self->fsm);
    nn_sipc_init (&self->sipc, NN_CIPC_SRC_SIPC, ep, &self->fsm);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    return 0;
}