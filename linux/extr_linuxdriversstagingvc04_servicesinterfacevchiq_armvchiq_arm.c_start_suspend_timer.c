#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {int suspend_timer_running; TYPE_3__ suspend_timer; int /*<<< orphan*/  suspend_timer_timeout; } ;
typedef  TYPE_1__ VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

inline void
start_suspend_timer(VCHIQ_ARM_STATE_T *arm_state)
{
	del_timer(&arm_state->suspend_timer);
	arm_state->suspend_timer.expires = jiffies +
		msecs_to_jiffies(arm_state->suspend_timer_timeout);
	add_timer(&arm_state->suspend_timer);
	arm_state->suspend_timer_running = 1;
}