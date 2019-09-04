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
typedef  int u32 ;
struct scsi_disk {int index; int media_present; int first_scan; int /*<<< orphan*/  dev; scalar_t__ opal_dev; scalar_t__ security; scalar_t__ capacity; int /*<<< orphan*/  max_medium_access_timeouts; scalar_t__ ATO; scalar_t__ RCD; scalar_t__ WCE; scalar_t__ cache_override; scalar_t__ write_prot; struct scsi_device* device; int /*<<< orphan*/  driver; struct gendisk* disk; } ;
struct device {int dummy; } ;
struct scsi_device {int sector_size; scalar_t__ removable; int /*<<< orphan*/  request_queue; struct device sdev_gendev; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  events; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue; int /*<<< orphan*/ * private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GENHD_FL_REMOVABLE ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  SD_MAX_MEDIUM_TIMEOUTS ; 
 int /*<<< orphan*/  blk_pm_runtime_init (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  device_add_disk (struct device*,struct gendisk*) ; 
 scalar_t__ init_opal_dev (struct scsi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (struct scsi_device*) ; 
 int /*<<< orphan*/  sd_dif_config_host (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_fops ; 
 int /*<<< orphan*/  sd_major (int) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,...) ; 
 int /*<<< orphan*/  sd_revalidate_disk (struct gendisk*) ; 
 int /*<<< orphan*/  sd_sec_submit ; 

__attribute__((used)) static void sd_probe_async(void *data, async_cookie_t cookie)
{
	struct scsi_disk *sdkp = data;
	struct scsi_device *sdp;
	struct gendisk *gd;
	u32 index;
	struct device *dev;

	sdp = sdkp->device;
	gd = sdkp->disk;
	index = sdkp->index;
	dev = &sdp->sdev_gendev;

	gd->major = sd_major((index & 0xf0) >> 4);
	gd->first_minor = ((index & 0xf) << 4) | (index & 0xfff00);

	gd->fops = &sd_fops;
	gd->private_data = &sdkp->driver;
	gd->queue = sdkp->device->request_queue;

	/* defaults, until the device tells us otherwise */
	sdp->sector_size = 512;
	sdkp->capacity = 0;
	sdkp->media_present = 1;
	sdkp->write_prot = 0;
	sdkp->cache_override = 0;
	sdkp->WCE = 0;
	sdkp->RCD = 0;
	sdkp->ATO = 0;
	sdkp->first_scan = 1;
	sdkp->max_medium_access_timeouts = SD_MAX_MEDIUM_TIMEOUTS;

	sd_revalidate_disk(gd);

	gd->flags = GENHD_FL_EXT_DEVT;
	if (sdp->removable) {
		gd->flags |= GENHD_FL_REMOVABLE;
		gd->events |= DISK_EVENT_MEDIA_CHANGE;
	}

	blk_pm_runtime_init(sdp->request_queue, dev);
	device_add_disk(dev, gd);
	if (sdkp->capacity)
		sd_dif_config_host(sdkp);

	sd_revalidate_disk(gd);

	if (sdkp->security) {
		sdkp->opal_dev = init_opal_dev(sdp, &sd_sec_submit);
		if (sdkp->opal_dev)
			sd_printk(KERN_NOTICE, sdkp, "supports TCG Opal\n");
	}

	sd_printk(KERN_NOTICE, sdkp, "Attached SCSI %sdisk\n",
		  sdp->removable ? "removable " : "");
	scsi_autopm_put_device(sdp);
	put_device(&sdkp->dev);
}