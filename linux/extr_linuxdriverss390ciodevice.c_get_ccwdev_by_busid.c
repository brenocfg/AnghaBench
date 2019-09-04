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
struct device {int dummy; } ;
struct ccw_driver {int /*<<< orphan*/  driver; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccwdev_check_busid ; 
 struct device* driver_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

struct ccw_device *get_ccwdev_by_busid(struct ccw_driver *cdrv,
				       const char *bus_id)
{
	struct device *dev;

	dev = driver_find_device(&cdrv->driver, NULL, (void *)bus_id,
				 __ccwdev_check_busid);

	return dev ? to_ccwdev(dev) : NULL;
}