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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PM_SUSPEND_MAX ; 
 scalar_t__ PM_SUSPEND_MEM ; 
 scalar_t__ PM_SUSPEND_ON ; 
 scalar_t__ decode_state (char const*,size_t) ; 
 int hibernate () ; 
 scalar_t__ mem_sleep_current ; 
 int pm_autosleep_lock () ; 
 scalar_t__ pm_autosleep_state () ; 
 int /*<<< orphan*/  pm_autosleep_unlock () ; 
 int pm_suspend (scalar_t__) ; 

__attribute__((used)) static ssize_t state_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
	suspend_state_t state;
	int error;

	error = pm_autosleep_lock();
	if (error)
		return error;

	if (pm_autosleep_state() > PM_SUSPEND_ON) {
		error = -EBUSY;
		goto out;
	}

	state = decode_state(buf, n);
	if (state < PM_SUSPEND_MAX) {
		if (state == PM_SUSPEND_MEM)
			state = mem_sleep_current;

		error = pm_suspend(state);
	} else if (state == PM_SUSPEND_MAX) {
		error = hibernate();
	} else {
		error = -EINVAL;
	}

 out:
	pm_autosleep_unlock();
	return error ? error : n;
}