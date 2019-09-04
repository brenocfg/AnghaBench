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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int CCWDEV_ALLOW_FORCE ; 
 int CCWDEV_DO_MULTIPATH ; 
 int CCWDEV_DO_PATHGROUP ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,struct ccw_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int ccw_device_set_options (struct ccw_device*,int) ; 
 int /*<<< orphan*/  dasd_eckd_discipline ; 
 int dasd_generic_probe (struct ccw_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dasd_eckd_probe (struct ccw_device *cdev)
{
	int ret;

	/* set ECKD specific ccw-device options */
	ret = ccw_device_set_options(cdev, CCWDEV_ALLOW_FORCE |
				     CCWDEV_DO_PATHGROUP | CCWDEV_DO_MULTIPATH);
	if (ret) {
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s",
				"dasd_eckd_probe: could not set "
				"ccw-device options");
		return ret;
	}
	ret = dasd_generic_probe(cdev, &dasd_eckd_discipline);
	return ret;
}