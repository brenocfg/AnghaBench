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
struct nn_fsm {int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_isidle (struct nn_fsm*) ; 

void nn_fsm_term (struct nn_fsm *self)
{
    nn_assert (nn_fsm_isidle (self));
    nn_fsm_event_term (&self->stopped);
}