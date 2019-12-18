#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nn_ep {int dummy; } ;
struct TYPE_4__ {int state; } ;
struct nn_binproc {int /*<<< orphan*/  item; TYPE_1__ fsm; int /*<<< orphan*/  sinprocs; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BINPROC_STATE_IDLE ; 
 int /*<<< orphan*/  alloc_assert (struct nn_binproc*) ; 
 struct nn_binproc* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_binproc_connect ; 
 int /*<<< orphan*/  nn_binproc_handler ; 
 int /*<<< orphan*/  nn_binproc_ops ; 
 int /*<<< orphan*/  nn_binproc_shutdown ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_binproc*) ; 
 int /*<<< orphan*/  nn_free (struct nn_binproc*) ; 
 int /*<<< orphan*/  nn_fsm_init_root (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (TYPE_1__*) ; 
 int /*<<< orphan*/  nn_fsm_term (TYPE_1__*) ; 
 int nn_ins_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ins_item_init (int /*<<< orphan*/ *,struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ins_item_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 

int nn_binproc_create (struct nn_ep *ep)
{
    int rc;
    struct nn_binproc *self;

    self = nn_alloc (sizeof (struct nn_binproc), "binproc");
    alloc_assert (self);

    nn_ins_item_init (&self->item, ep);
    nn_fsm_init_root (&self->fsm, nn_binproc_handler, nn_binproc_shutdown,
        nn_ep_getctx (ep));
    self->state = NN_BINPROC_STATE_IDLE;
    nn_list_init (&self->sinprocs);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    /*  Register the inproc endpoint into a global repository. */
    rc = nn_ins_bind (&self->item, nn_binproc_connect);
    if (rc < 0) {
        nn_list_term (&self->sinprocs);

        /*  TODO: Now, this is ugly! We are getting the state machine into
            the idle state manually. How should it be done correctly? */
        self->fsm.state = 1;
        nn_fsm_term (&self->fsm);

        nn_ins_item_term (&self->item);
        nn_free (self);
        return rc;
    }

    nn_ep_tran_setup (ep, &nn_binproc_ops, self);
    return 0;
}