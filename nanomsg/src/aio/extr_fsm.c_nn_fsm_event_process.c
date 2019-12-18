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
struct nn_fsm_event {int src; int type; int /*<<< orphan*/  fsm; int /*<<< orphan*/ * srcptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fsm_feed (int /*<<< orphan*/ ,int,int,void*) ; 

void nn_fsm_event_process (struct nn_fsm_event *self)
{
    int src;
    int type;
    void *srcptr;

    src = self->src;
    type = self->type;
    srcptr = self->srcptr;
    self->src = -1;
    self->type = -1;
    self->srcptr = NULL;

    nn_fsm_feed (self->fsm, src, type, srcptr);
}