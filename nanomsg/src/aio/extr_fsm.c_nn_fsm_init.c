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
struct nn_fsm {int src; int /*<<< orphan*/  stopped; int /*<<< orphan*/  ctx; struct nn_fsm* owner; void* srcptr; int /*<<< orphan*/  state; void* shutdown_fn; void* fn; } ;
typedef  void* nn_fsm_fn ;

/* Variables and functions */
 int /*<<< orphan*/  NN_FSM_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 

void nn_fsm_init (struct nn_fsm *self, nn_fsm_fn fn,
    nn_fsm_fn shutdown_fn, int src, void *srcptr, struct nn_fsm *owner)
{
    self->fn = fn;
    self->shutdown_fn = shutdown_fn;
    self->state = NN_FSM_STATE_IDLE;
    self->src = src;
    self->srcptr = srcptr;
    self->owner = owner;
    self->ctx = owner->ctx;
    nn_fsm_event_init (&self->stopped);
}