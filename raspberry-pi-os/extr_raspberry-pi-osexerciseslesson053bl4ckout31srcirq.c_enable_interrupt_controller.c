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

/* Variables and functions */
 int /*<<< orphan*/  TIMER_INT_CTRL_0 ; 
 int /*<<< orphan*/  TIMER_INT_CTRL_0_VALUE ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void enable_interrupt_controller()
{
    // Enables Core 0 Timers interrupt control for the generic timer 
    put32(TIMER_INT_CTRL_0, TIMER_INT_CTRL_0_VALUE);
}