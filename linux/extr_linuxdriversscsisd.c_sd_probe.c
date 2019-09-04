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
struct device {int /*<<< orphan*/ * class; struct device* parent; } ;
struct scsi_disk {int index; struct device dev; struct scsi_device* device; int /*<<< orphan*/  openers; struct gendisk* disk; int /*<<< orphan*/ * driver; } ;
struct scsi_device {scalar_t__ type; TYPE_1__* request_queue; int /*<<< orphan*/  ioerr_cnt; } ;
struct gendisk {int /*<<< orphan*/  disk_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_NAME_LEN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_MINORS ; 
 int /*<<< orphan*/  SD_MOD_TIMEOUT ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_MOD ; 
 scalar_t__ TYPE_RBC ; 
 scalar_t__ TYPE_ZBC ; 
 struct gendisk* alloc_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_schedule_domain (int /*<<< orphan*/ ,struct scsi_disk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct scsi_disk*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct scsi_disk*) ; 
 struct scsi_disk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_sd_probe_domain ; 
 int /*<<< orphan*/  sd_disk_class ; 
 int sd_format_disk_name (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_index_ida ; 
 int /*<<< orphan*/  sd_probe_async ; 
 int /*<<< orphan*/  sd_template ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int sd_probe(struct device *dev)
{
	struct scsi_device *sdp = to_scsi_device(dev);
	struct scsi_disk *sdkp;
	struct gendisk *gd;
	int index;
	int error;

	scsi_autopm_get_device(sdp);
	error = -ENODEV;
	if (sdp->type != TYPE_DISK &&
	    sdp->type != TYPE_ZBC &&
	    sdp->type != TYPE_MOD &&
	    sdp->type != TYPE_RBC)
		goto out;

#ifndef CONFIG_BLK_DEV_ZONED
	if (sdp->type == TYPE_ZBC)
		goto out;
#endif
	SCSI_LOG_HLQUEUE(3, sdev_printk(KERN_INFO, sdp,
					"sd_probe\n"));

	error = -ENOMEM;
	sdkp = kzalloc(sizeof(*sdkp), GFP_KERNEL);
	if (!sdkp)
		goto out;

	gd = alloc_disk(SD_MINORS);
	if (!gd)
		goto out_free;

	index = ida_alloc(&sd_index_ida, GFP_KERNEL);
	if (index < 0) {
		sdev_printk(KERN_WARNING, sdp, "sd_probe: memory exhausted.\n");
		goto out_put;
	}

	error = sd_format_disk_name("sd", index, gd->disk_name, DISK_NAME_LEN);
	if (error) {
		sdev_printk(KERN_WARNING, sdp, "SCSI disk (sd) name length exceeded.\n");
		goto out_free_index;
	}

	sdkp->device = sdp;
	sdkp->driver = &sd_template;
	sdkp->disk = gd;
	sdkp->index = index;
	atomic_set(&sdkp->openers, 0);
	atomic_set(&sdkp->device->ioerr_cnt, 0);

	if (!sdp->request_queue->rq_timeout) {
		if (sdp->type != TYPE_MOD)
			blk_queue_rq_timeout(sdp->request_queue, SD_TIMEOUT);
		else
			blk_queue_rq_timeout(sdp->request_queue,
					     SD_MOD_TIMEOUT);
	}

	device_initialize(&sdkp->dev);
	sdkp->dev.parent = dev;
	sdkp->dev.class = &sd_disk_class;
	dev_set_name(&sdkp->dev, "%s", dev_name(dev));

	error = device_add(&sdkp->dev);
	if (error)
		goto out_free_index;

	get_device(dev);
	dev_set_drvdata(dev, sdkp);

	get_device(&sdkp->dev);	/* prevent release before async_schedule */
	async_schedule_domain(sd_probe_async, sdkp, &scsi_sd_probe_domain);

	return 0;

 out_free_index:
	ida_free(&sd_index_ida, index);
 out_put:
	put_disk(gd);
 out_free:
	kfree(sdkp);
 out:
	scsi_autopm_put_device(sdp);
	return error;
}