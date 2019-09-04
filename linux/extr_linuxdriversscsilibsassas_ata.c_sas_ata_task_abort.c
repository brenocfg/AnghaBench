#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_task {struct ata_queued_cmd* uldd_task; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct completion {int dummy; } ;
struct ata_queued_cmd {struct completion* private_data; int /*<<< orphan*/  err_mask; int /*<<< orphan*/  flags; TYPE_1__* scsicmd; } ;
struct TYPE_4__ {struct request_queue* request_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  request; TYPE_2__* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ATA_QCFLAG_ACTIVE ; 
 int /*<<< orphan*/  ATA_QCFLAG_FAILED ; 
 int /*<<< orphan*/  blk_abort_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void sas_ata_task_abort(struct sas_task *task)
{
	struct ata_queued_cmd *qc = task->uldd_task;
	struct completion *waiting;

	/* Bounce SCSI-initiated commands to the SCSI EH */
	if (qc->scsicmd) {
		struct request_queue *q = qc->scsicmd->device->request_queue;
		unsigned long flags;

		spin_lock_irqsave(q->queue_lock, flags);
		blk_abort_request(qc->scsicmd->request);
		spin_unlock_irqrestore(q->queue_lock, flags);
		return;
	}

	/* Internal command, fake a timeout and complete. */
	qc->flags &= ~ATA_QCFLAG_ACTIVE;
	qc->flags |= ATA_QCFLAG_FAILED;
	qc->err_mask |= AC_ERR_TIMEOUT;
	waiting = qc->private_data;
	complete(waiting);
}