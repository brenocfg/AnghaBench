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
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; int /*<<< orphan*/  shost_dev; int /*<<< orphan*/  host_lock; int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  tmf_work_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int /*<<< orphan*/  SHOST_CANCEL ; 
 int /*<<< orphan*/  SHOST_CANCEL_RECOVERY ; 
 int /*<<< orphan*/  SHOST_DEL ; 
 int /*<<< orphan*/  SHOST_DEL_RECOVERY ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_autopm_get_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_forget_host (struct Scsi_Host*) ; 
 scalar_t__ scsi_host_set_state (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_proc_host_rm (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  transport_unregister_device (int /*<<< orphan*/ *) ; 

void scsi_remove_host(struct Scsi_Host *shost)
{
	unsigned long flags;

	mutex_lock(&shost->scan_mutex);
	spin_lock_irqsave(shost->host_lock, flags);
	if (scsi_host_set_state(shost, SHOST_CANCEL))
		if (scsi_host_set_state(shost, SHOST_CANCEL_RECOVERY)) {
			spin_unlock_irqrestore(shost->host_lock, flags);
			mutex_unlock(&shost->scan_mutex);
			return;
		}
	spin_unlock_irqrestore(shost->host_lock, flags);

	scsi_autopm_get_host(shost);
	flush_workqueue(shost->tmf_work_q);
	scsi_forget_host(shost);
	mutex_unlock(&shost->scan_mutex);
	scsi_proc_host_rm(shost);

	spin_lock_irqsave(shost->host_lock, flags);
	if (scsi_host_set_state(shost, SHOST_DEL))
		BUG_ON(scsi_host_set_state(shost, SHOST_DEL_RECOVERY));
	spin_unlock_irqrestore(shost->host_lock, flags);

	transport_unregister_device(&shost->shost_gendev);
	device_unregister(&shost->shost_dev);
	device_del(&shost->shost_gendev);
}