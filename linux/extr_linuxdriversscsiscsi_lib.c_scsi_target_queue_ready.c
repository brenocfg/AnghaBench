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
struct scsi_target {unsigned int can_queue; int /*<<< orphan*/  target_busy; int /*<<< orphan*/  target_blocked; struct scsi_device* starget_sdev_user; scalar_t__ single_lun; } ;
struct scsi_device {int /*<<< orphan*/  starved_entry; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  starved_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  starget_printk (int /*<<< orphan*/ ,struct scsi_target*,char*) ; 

__attribute__((used)) static inline int scsi_target_queue_ready(struct Scsi_Host *shost,
					   struct scsi_device *sdev)
{
	struct scsi_target *starget = scsi_target(sdev);
	unsigned int busy;

	if (starget->single_lun) {
		spin_lock_irq(shost->host_lock);
		if (starget->starget_sdev_user &&
		    starget->starget_sdev_user != sdev) {
			spin_unlock_irq(shost->host_lock);
			return 0;
		}
		starget->starget_sdev_user = sdev;
		spin_unlock_irq(shost->host_lock);
	}

	if (starget->can_queue <= 0)
		return 1;

	busy = atomic_inc_return(&starget->target_busy) - 1;
	if (atomic_read(&starget->target_blocked) > 0) {
		if (busy)
			goto starved;

		/*
		 * unblock after target_blocked iterates to zero
		 */
		if (atomic_dec_return(&starget->target_blocked) > 0)
			goto out_dec;

		SCSI_LOG_MLQUEUE(3, starget_printk(KERN_INFO, starget,
				 "unblocking target at zero depth\n"));
	}

	if (busy >= starget->can_queue)
		goto starved;

	return 1;

starved:
	spin_lock_irq(shost->host_lock);
	list_move_tail(&sdev->starved_entry, &shost->starved_list);
	spin_unlock_irq(shost->host_lock);
out_dec:
	if (starget->can_queue > 0)
		atomic_dec(&starget->target_busy);
	return 0;
}