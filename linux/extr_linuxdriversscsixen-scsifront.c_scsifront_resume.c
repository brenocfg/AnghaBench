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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct vscsifrnt_info {struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateInitialised ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct vscsifrnt_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsifront_finish_all (struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  scsifront_free_ring (struct vscsifrnt_info*) ; 
 int scsifront_init_ring (struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsifront_resume(struct xenbus_device *dev)
{
	struct vscsifrnt_info *info = dev_get_drvdata(&dev->dev);
	struct Scsi_Host *host = info->host;
	int err;

	spin_lock_irq(host->host_lock);

	/* Finish all still pending commands. */
	scsifront_finish_all(info);

	spin_unlock_irq(host->host_lock);

	/* Reconnect to dom0. */
	scsifront_free_ring(info);
	err = scsifront_init_ring(info);
	if (err) {
		dev_err(&dev->dev, "fail to resume %d\n", err);
		scsi_host_put(host);
		return err;
	}

	xenbus_switch_state(dev, XenbusStateInitialised);

	return 0;
}