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
struct watchdog_device {unsigned int timeout; } ;
struct device {int /*<<< orphan*/ * of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 int /*<<< orphan*/  watchdog_check_min_max_timeout (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_timeout_invalid (struct watchdog_device*,unsigned int) ; 

int watchdog_init_timeout(struct watchdog_device *wdd,
				unsigned int timeout_parm, struct device *dev)
{
	unsigned int t = 0;
	int ret = 0;

	watchdog_check_min_max_timeout(wdd);

	/* try to get the timeout module parameter first */
	if (!watchdog_timeout_invalid(wdd, timeout_parm) && timeout_parm) {
		wdd->timeout = timeout_parm;
		return ret;
	}
	if (timeout_parm)
		ret = -EINVAL;

	/* try to get the timeout_sec property */
	if (dev == NULL || dev->of_node == NULL)
		return ret;
	of_property_read_u32(dev->of_node, "timeout-sec", &t);
	if (!watchdog_timeout_invalid(wdd, t) && t)
		wdd->timeout = t;
	else
		ret = -EINVAL;

	return ret;
}