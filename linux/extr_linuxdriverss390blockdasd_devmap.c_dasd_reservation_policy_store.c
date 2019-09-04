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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ccw_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FEATURE_FAILONSLCK ; 
 int EINVAL ; 
 int dasd_set_feature (struct ccw_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sysfs_streq (char*,char const*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t dasd_reservation_policy_store(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	int rc;

	if (sysfs_streq("ignore", buf))
		rc = dasd_set_feature(cdev, DASD_FEATURE_FAILONSLCK, 0);
	else if (sysfs_streq("fail", buf))
		rc = dasd_set_feature(cdev, DASD_FEATURE_FAILONSLCK, 1);
	else
		rc = -EINVAL;

	return rc ? : count;
}