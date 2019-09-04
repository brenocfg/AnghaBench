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
struct vscsifrnt_info {int pause; int waiting_pause; int /*<<< orphan*/  wq_pause; int /*<<< orphan*/  wq_sync; scalar_t__ wait_ring_available; scalar_t__ callers; struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 struct vscsifrnt_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scsifront_suspend(struct xenbus_device *dev)
{
	struct vscsifrnt_info *info = dev_get_drvdata(&dev->dev);
	struct Scsi_Host *host = info->host;
	int err = 0;

	/* No new commands for the backend. */
	spin_lock_irq(host->host_lock);
	info->pause = 1;
	while (info->callers && !err) {
		info->waiting_pause = 1;
		info->wait_ring_available = 0;
		spin_unlock_irq(host->host_lock);
		wake_up(&info->wq_sync);
		err = wait_event_interruptible(info->wq_pause,
					       !info->waiting_pause);
		spin_lock_irq(host->host_lock);
	}
	spin_unlock_irq(host->host_lock);
	return err;
}