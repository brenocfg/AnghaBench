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
struct nn_timer {int timeout; int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 

void nn_timer_start (struct nn_timer *self, int timeout)
{
    /*  Negative timeout make no sense. */
    nn_assert (timeout >= 0);

    self->timeout = timeout;
    nn_fsm_start (&self->fsm);
}