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
typedef  scalar_t__ suspend_state_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PM_SUSPEND_MAX ; 
 scalar_t__ PM_SUSPEND_ON ; 
 int /*<<< orphan*/  __pm_relax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autosleep_lock ; 
 scalar_t__ autosleep_state ; 
 int /*<<< orphan*/  autosleep_ws ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_wakep_autosleep_enabled (int) ; 
 int /*<<< orphan*/  queue_up_suspend_work () ; 

int pm_autosleep_set_state(suspend_state_t state)
{

#ifndef CONFIG_HIBERNATION
	if (state >= PM_SUSPEND_MAX)
		return -EINVAL;
#endif

	__pm_stay_awake(autosleep_ws);

	mutex_lock(&autosleep_lock);

	autosleep_state = state;

	__pm_relax(autosleep_ws);

	if (state > PM_SUSPEND_ON) {
		pm_wakep_autosleep_enabled(true);
		queue_up_suspend_work();
	} else {
		pm_wakep_autosleep_enabled(false);
	}

	mutex_unlock(&autosleep_lock);
	return 0;
}