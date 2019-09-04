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
struct ipr_ioa_cfg {TYPE_2__* host; TYPE_1__* vpd_cbs; } ;
struct ipr_inquiry_page3 {int major_release; int card_type; int /*<<< orphan*/ * minor_release; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {struct ipr_inquiry_page3 page3_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t ipr_show_fw_version(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)shost->hostdata;
	struct ipr_inquiry_page3 *ucode_vpd = &ioa_cfg->vpd_cbs->page3_data;
	unsigned long lock_flags = 0;
	int len;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	len = snprintf(buf, PAGE_SIZE, "%02X%02X%02X%02X\n",
		       ucode_vpd->major_release, ucode_vpd->card_type,
		       ucode_vpd->minor_release[0],
		       ucode_vpd->minor_release[1]);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return len;
}