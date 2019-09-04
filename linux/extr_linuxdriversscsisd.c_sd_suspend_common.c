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
struct scsi_sense_hdr {scalar_t__ sense_key; } ;
struct scsi_disk {TYPE_1__* device; scalar_t__ media_present; scalar_t__ WCE; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ manage_start_stop; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 struct scsi_disk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int sd_start_stop_device (struct scsi_disk*,int /*<<< orphan*/ ) ; 
 int sd_sync_cache (struct scsi_disk*,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int sd_suspend_common(struct device *dev, bool ignore_stop_errors)
{
	struct scsi_disk *sdkp = dev_get_drvdata(dev);
	struct scsi_sense_hdr sshdr;
	int ret = 0;

	if (!sdkp)	/* E.g.: runtime suspend following sd_remove() */
		return 0;

	if (sdkp->WCE && sdkp->media_present) {
		sd_printk(KERN_NOTICE, sdkp, "Synchronizing SCSI cache\n");
		ret = sd_sync_cache(sdkp, &sshdr);

		if (ret) {
			/* ignore OFFLINE device */
			if (ret == -ENODEV)
				return 0;

			if (!scsi_sense_valid(&sshdr) ||
			    sshdr.sense_key != ILLEGAL_REQUEST)
				return ret;

			/*
			 * sshdr.sense_key == ILLEGAL_REQUEST means this drive
			 * doesn't support sync. There's not much to do and
			 * suspend shouldn't fail.
			 */
			ret = 0;
		}
	}

	if (sdkp->device->manage_start_stop) {
		sd_printk(KERN_NOTICE, sdkp, "Stopping disk\n");
		/* an error is not worth aborting a system sleep */
		ret = sd_start_stop_device(sdkp, 0);
		if (ignore_stop_errors)
			ret = 0;
	}

	return ret;
}