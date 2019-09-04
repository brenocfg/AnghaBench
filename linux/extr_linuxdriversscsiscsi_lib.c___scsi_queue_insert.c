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
struct scsi_device {int /*<<< orphan*/  requeue_work; int /*<<< orphan*/  sdev_gendev; struct request_queue* request_queue; } ;
struct scsi_cmnd {int /*<<< orphan*/  request; scalar_t__ result; struct scsi_device* device; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_device_unbusy (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_set_blocked (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void __scsi_queue_insert(struct scsi_cmnd *cmd, int reason, bool unbusy)
{
	struct scsi_device *device = cmd->device;
	struct request_queue *q = device->request_queue;
	unsigned long flags;

	SCSI_LOG_MLQUEUE(1, scmd_printk(KERN_INFO, cmd,
		"Inserting command %p into mlqueue\n", cmd));

	scsi_set_blocked(cmd, reason);

	/*
	 * Decrement the counters, since these commands are no longer
	 * active on the host/device.
	 */
	if (unbusy)
		scsi_device_unbusy(device);

	/*
	 * Requeue this command.  It will go before all other commands
	 * that are already in the queue. Schedule requeue work under
	 * lock such that the kblockd_schedule_work() call happens
	 * before blk_cleanup_queue() finishes.
	 */
	cmd->result = 0;
	if (q->mq_ops) {
		/*
		 * Before a SCSI command is dispatched,
		 * get_device(&sdev->sdev_gendev) is called and the host,
		 * target and device busy counters are increased. Since
		 * requeuing a request causes these actions to be repeated and
		 * since scsi_device_unbusy() has already been called,
		 * put_device(&device->sdev_gendev) must still be called. Call
		 * put_device() after blk_mq_requeue_request() to avoid that
		 * removal of the SCSI device can start before requeueing has
		 * happened.
		 */
		blk_mq_requeue_request(cmd->request, true);
		put_device(&device->sdev_gendev);
		return;
	}
	spin_lock_irqsave(q->queue_lock, flags);
	blk_requeue_request(q, cmd->request);
	kblockd_schedule_work(&device->requeue_work);
	spin_unlock_irqrestore(q->queue_lock, flags);
}