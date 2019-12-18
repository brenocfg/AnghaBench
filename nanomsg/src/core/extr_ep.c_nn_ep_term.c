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
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ) ;} ;
struct nn_ep {int /*<<< orphan*/  fsm; int /*<<< orphan*/  item; int /*<<< orphan*/  tran; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_EP_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_item_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void nn_ep_term (struct nn_ep *self)
{
    nn_assert_state (self, NN_EP_STATE_IDLE);

    self->ops.destroy (self->tran);
    nn_list_item_term (&self->item);
    nn_fsm_term (&self->fsm);
}