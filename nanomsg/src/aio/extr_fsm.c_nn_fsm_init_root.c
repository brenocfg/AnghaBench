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
struct nn_fsm {int src; int /*<<< orphan*/  stopped; struct nn_ctx* ctx; int /*<<< orphan*/ * owner; int /*<<< orphan*/ * srcptr; int /*<<< orphan*/  state; void* shutdown_fn; void* fn; } ;
struct nn_ctx {int dummy; } ;
typedef  void* nn_fsm_fn ;

/* Variables and functions */
 int /*<<< orphan*/  NN_FSM_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 

void nn_fsm_init_root (struct nn_fsm *self, nn_fsm_fn fn,
    nn_fsm_fn shutdown_fn, struct nn_ctx *ctx)
{
    self->fn = fn;
    self->shutdown_fn = shutdown_fn;
    self->state = NN_FSM_STATE_IDLE;
    self->src = -1;
    self->srcptr = NULL;
    self->owner = NULL;
    self->ctx = ctx;
    nn_fsm_event_init (&self->stopped);
}