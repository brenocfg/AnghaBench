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
struct nn_bipc {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  aipcs; int /*<<< orphan*/ * aipc; int /*<<< orphan*/  state; struct nn_ep* ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BIPC_SRC_USOCK ; 
 int /*<<< orphan*/  NN_BIPC_STATE_IDLE ; 
 int /*<<< orphan*/  alloc_assert (struct nn_bipc*) ; 
 struct nn_bipc* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_bipc_ep_ops ; 
 int /*<<< orphan*/  nn_bipc_handler ; 
 int nn_bipc_listen (struct nn_bipc*) ; 
 int /*<<< orphan*/  nn_bipc_shutdown ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_bipc*) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nn_bipc_create (struct nn_ep *ep)
{
    struct nn_bipc *self;
    int rc;

    /*  Allocate the new endpoint object. */
    self = nn_alloc (sizeof (struct nn_bipc), "bipc");
    alloc_assert (self);


    /*  Initialise the structure. */
    self->ep = ep;
    nn_ep_tran_setup (ep, &nn_bipc_ep_ops, self);
    nn_fsm_init_root (&self->fsm, nn_bipc_handler, nn_bipc_shutdown,
        nn_ep_getctx (ep));
    self->state = NN_BIPC_STATE_IDLE;
    self->aipc = NULL;
    nn_list_init (&self->aipcs);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    nn_usock_init (&self->usock, NN_BIPC_SRC_USOCK, &self->fsm);

    rc = nn_bipc_listen (self);
    if (rc != 0) {
        return rc;
    }

    return 0;
}