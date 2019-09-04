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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int __watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int watchdog_deferred_registration_add (struct watchdog_device*) ; 
 scalar_t__ wtd_deferred_reg_done ; 
 int /*<<< orphan*/  wtd_deferred_reg_mutex ; 

int watchdog_register_device(struct watchdog_device *wdd)
{
	int ret;

	mutex_lock(&wtd_deferred_reg_mutex);
	if (wtd_deferred_reg_done)
		ret = __watchdog_register_device(wdd);
	else
		ret = watchdog_deferred_registration_add(wdd);
	mutex_unlock(&wtd_deferred_reg_mutex);
	return ret;
}