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
struct nn_fsm {scalar_t__ state; int /*<<< orphan*/  (* shutdown_fn ) (struct nn_fsm*,int,int,void*) ;int /*<<< orphan*/  (* fn ) (struct nn_fsm*,int,int,void*) ;} ;

/* Variables and functions */
 scalar_t__ NN_FSM_STATE_STOPPING ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  stub1 (struct nn_fsm*,int,int,void*) ; 
 int /*<<< orphan*/  stub2 (struct nn_fsm*,int,int,void*) ; 

void nn_fsm_feed (struct nn_fsm *self, int src, int type, void *srcptr)
{
    if (nn_slow (self->state != NN_FSM_STATE_STOPPING)) {
        self->fn (self, src, type, srcptr);
    } else {
        self->shutdown_fn (self, src, type, srcptr);
    }
}