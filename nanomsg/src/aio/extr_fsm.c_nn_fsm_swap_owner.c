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
struct nn_fsm_owner {int src; struct nn_fsm* fsm; } ;
struct nn_fsm {int src; struct nn_fsm* owner; } ;

/* Variables and functions */

void nn_fsm_swap_owner (struct nn_fsm *self, struct nn_fsm_owner *owner)
{
    int oldsrc;
    struct nn_fsm *oldowner;

    oldsrc = self->src;
    oldowner = self->owner;
    self->src = owner->src;
    self->owner = owner->fsm;
    owner->src = oldsrc;
    owner->fsm = oldowner;
}