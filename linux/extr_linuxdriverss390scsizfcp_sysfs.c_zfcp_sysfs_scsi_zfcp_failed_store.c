#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 TYPE_2__* sdev_to_zfcp (struct scsi_device*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 int /*<<< orphan*/  zfcp_erp_lun_reopen (struct scsi_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_set_lun_status (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_scsi_zfcp_failed_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	unsigned long val;

	if (kstrtoul(buf, 0, &val) || val != 0)
		return -EINVAL;

	zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_lun_reopen(sdev, ZFCP_STATUS_COMMON_ERP_FAILED,
			    "syufai3");
	zfcp_erp_wait(sdev_to_zfcp(sdev)->port->adapter);

	return count;
}