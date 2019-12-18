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
struct nn_worker_timer {int /*<<< orphan*/  hndl; struct nn_fsm* owner; } ;
struct nn_fsm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_timerset_hndl_init (int /*<<< orphan*/ *) ; 

void nn_worker_timer_init (struct nn_worker_timer *self, struct nn_fsm *owner)
{
    self->owner = owner;
    nn_timerset_hndl_init (&self->hndl);
}