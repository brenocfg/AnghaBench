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
struct consw {int dummy; } ;
struct con_driver {int /*<<< orphan*/  flag; struct consw const* con; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_DRIVER_FLAG_ZOMBIE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int MAX_NR_CON_DRIVER ; 
 int /*<<< orphan*/  con_driver_unregister_work ; 
 scalar_t__ con_is_bound (struct consw const*) ; 
 struct consw const* conswitchp ; 
 struct con_driver* registered_con_driver ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int do_unregister_con_driver(const struct consw *csw)
{
	int i;

	/* cannot unregister a bound driver */
	if (con_is_bound(csw))
		return -EBUSY;

	if (csw == conswitchp)
		return -EINVAL;

	for (i = 0; i < MAX_NR_CON_DRIVER; i++) {
		struct con_driver *con_driver = &registered_con_driver[i];

		if (con_driver->con == csw) {
			/*
			 * Defer the removal of the sysfs entries since that
			 * will acquire the kernfs s_active lock and we can't
			 * acquire this lock while holding the console lock:
			 * the unbind sysfs entry imposes already the opposite
			 * order. Reset con already here to prevent any later
			 * lookup to succeed and mark this slot as zombie, so
			 * it won't get reused until we complete the removal
			 * in the deferred work.
			 */
			con_driver->con = NULL;
			con_driver->flag = CON_DRIVER_FLAG_ZOMBIE;
			schedule_work(&con_driver_unregister_work);

			return 0;
		}
	}

	return -ENODEV;
}