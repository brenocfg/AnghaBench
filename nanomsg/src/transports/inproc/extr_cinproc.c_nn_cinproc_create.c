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
struct nn_cinproc {int /*<<< orphan*/  item; int /*<<< orphan*/  fsm; int /*<<< orphan*/  sinprocs; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_CINPROC_STATE_IDLE ; 
 int /*<<< orphan*/  NN_STAT_INPROGRESS_CONNECTIONS ; 
 int /*<<< orphan*/  alloc_assert (struct nn_cinproc*) ; 
 struct nn_cinproc* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_cinproc_connect ; 
 int /*<<< orphan*/  nn_cinproc_handler ; 
 int /*<<< orphan*/  nn_cinproc_ops ; 
 int /*<<< orphan*/  nn_cinproc_shutdown ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_stat_increment (struct nn_ep*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_cinproc*) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ins_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ins_item_init (int /*<<< orphan*/ *,struct nn_ep*) ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 

int nn_cinproc_create (struct nn_ep *ep)
{
    struct nn_cinproc *self;

    self = nn_alloc (sizeof (struct nn_cinproc), "cinproc");
    alloc_assert (self);

    nn_ep_tran_setup (ep, &nn_cinproc_ops, self);

    nn_ins_item_init (&self->item, ep);
    nn_fsm_init_root (&self->fsm, nn_cinproc_handler, nn_cinproc_shutdown,
        nn_ep_getctx (ep));
    self->state = NN_CINPROC_STATE_IDLE;
    nn_list_init (&self->sinprocs);

    nn_ep_stat_increment (ep, NN_STAT_INPROGRESS_CONNECTIONS, 1);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    /*  Register the inproc endpoint into a global repository. */
    nn_ins_connect (&self->item, nn_cinproc_connect);

    return 0;
}