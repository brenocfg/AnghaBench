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
struct nn_surveyor {int /*<<< orphan*/  xsurveyor; int /*<<< orphan*/  fsm; int /*<<< orphan*/  timer; int /*<<< orphan*/  tosend; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_timer_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_xsurveyor_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_surveyor_term (struct nn_surveyor *self)
{
    nn_msg_term (&self->tosend);
    nn_timer_term (&self->timer);
    nn_fsm_term (&self->fsm);
    nn_xsurveyor_term (&self->xsurveyor);
}