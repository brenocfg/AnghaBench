#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_disk {int /*<<< orphan*/  opal_dev; TYPE_1__* device; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  manage_start_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 struct scsi_disk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  opal_unlock_from_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int sd_start_stop_device (struct scsi_disk*,int) ; 

__attribute__((used)) static int sd_resume(struct device *dev)
{
	struct scsi_disk *sdkp = dev_get_drvdata(dev);
	int ret;

	if (!sdkp)	/* E.g.: runtime resume at the start of sd_probe() */
		return 0;

	if (!sdkp->device->manage_start_stop)
		return 0;

	sd_printk(KERN_NOTICE, sdkp, "Starting disk\n");
	ret = sd_start_stop_device(sdkp, 1);
	if (!ret)
		opal_unlock_from_suspend(sdkp->opal_dev);
	return ret;
}