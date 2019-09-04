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
struct nvme_ctrl {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct nvme_ctrl* dev_get_drvdata (struct device*) ; 
 scalar_t__ device_remove_file_self (struct device*,struct device_attribute*) ; 
 int /*<<< orphan*/  nvme_delete_ctrl_sync (struct nvme_ctrl*) ; 

__attribute__((used)) static ssize_t nvme_sysfs_delete(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
	struct nvme_ctrl *ctrl = dev_get_drvdata(dev);

	if (device_remove_file_self(dev, attr))
		nvme_delete_ctrl_sync(ctrl);
	return count;
}