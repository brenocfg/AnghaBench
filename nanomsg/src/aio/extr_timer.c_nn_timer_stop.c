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
struct nn_timer {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fsm_stop (int /*<<< orphan*/ *) ; 

void nn_timer_stop (struct nn_timer *self)
{
    nn_fsm_stop (&self->fsm);
}