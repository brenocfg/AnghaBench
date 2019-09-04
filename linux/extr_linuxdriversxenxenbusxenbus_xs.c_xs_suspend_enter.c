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
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xs_state_exit_wq ; 
 int /*<<< orphan*/  xs_state_lock ; 
 scalar_t__ xs_state_users ; 
 int /*<<< orphan*/  xs_suspend_active ; 

__attribute__((used)) static void xs_suspend_enter(void)
{
	spin_lock(&xs_state_lock);
	xs_suspend_active++;
	spin_unlock(&xs_state_lock);
	wait_event(xs_state_exit_wq, xs_state_users == 0);
}