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
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct vscsifrnt_info {int host_active; struct Scsi_Host* host; int /*<<< orphan*/  shadow_lock; int /*<<< orphan*/  wq_pause; int /*<<< orphan*/  wq_sync; int /*<<< orphan*/  shadow_free_bitmap; struct xenbus_device* dev; } ;
struct Scsi_Host {int host_no; int max_sectors; int sg_tablesize; int /*<<< orphan*/  max_cmd_len; int /*<<< orphan*/  max_lun; scalar_t__ max_channel; int /*<<< orphan*/  max_id; scalar_t__ hostdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  VSCSIIF_MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  VSCSIIF_MAX_LUN ; 
 int /*<<< orphan*/  VSCSIIF_MAX_REQS ; 
 int /*<<< orphan*/  VSCSIIF_MAX_TARGET ; 
 int /*<<< orphan*/  XenbusStateInitialised ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsifront_free_ring (struct vscsifrnt_info*) ; 
 int scsifront_init_ring (struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  scsifront_sht ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsifront_probe(struct xenbus_device *dev,
			   const struct xenbus_device_id *id)
{
	struct vscsifrnt_info *info;
	struct Scsi_Host *host;
	int err = -ENOMEM;
	char name[TASK_COMM_LEN];

	host = scsi_host_alloc(&scsifront_sht, sizeof(*info));
	if (!host) {
		xenbus_dev_fatal(dev, err, "fail to allocate scsi host");
		return err;
	}
	info = (struct vscsifrnt_info *)host->hostdata;

	dev_set_drvdata(&dev->dev, info);
	info->dev = dev;

	bitmap_fill(info->shadow_free_bitmap, VSCSIIF_MAX_REQS);

	err = scsifront_init_ring(info);
	if (err) {
		scsi_host_put(host);
		return err;
	}

	init_waitqueue_head(&info->wq_sync);
	init_waitqueue_head(&info->wq_pause);
	spin_lock_init(&info->shadow_lock);

	snprintf(name, TASK_COMM_LEN, "vscsiif.%d", host->host_no);

	host->max_id      = VSCSIIF_MAX_TARGET;
	host->max_channel = 0;
	host->max_lun     = VSCSIIF_MAX_LUN;
	host->max_sectors = (host->sg_tablesize - 1) * PAGE_SIZE / 512;
	host->max_cmd_len = VSCSIIF_MAX_COMMAND_SIZE;

	err = scsi_add_host(host, &dev->dev);
	if (err) {
		dev_err(&dev->dev, "fail to add scsi host %d\n", err);
		goto free_sring;
	}
	info->host = host;
	info->host_active = 1;

	xenbus_switch_state(dev, XenbusStateInitialised);

	return 0;

free_sring:
	scsifront_free_ring(info);
	scsi_host_put(host);
	return err;
}