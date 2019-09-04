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
struct scsi_device {scalar_t__ hostdata; TYPE_1__* host; } ;
struct ipr_resource_entry {int /*<<< orphan*/  lun_wwn; int /*<<< orphan*/  dev_id; } ;
struct ipr_ioa_cfg {TYPE_2__* host; scalar_t__ sis64; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t ipr_show_device_id(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)sdev->host->hostdata;
	struct ipr_resource_entry *res;
	unsigned long lock_flags = 0;
	ssize_t len = -ENXIO;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (struct ipr_resource_entry *)sdev->hostdata;
	if (res && ioa_cfg->sis64)
		len = snprintf(buf, PAGE_SIZE, "0x%llx\n", be64_to_cpu(res->dev_id));
	else if (res)
		len = snprintf(buf, PAGE_SIZE, "0x%llx\n", res->lun_wwn);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return len;
}