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
struct scsi_device {struct request_queue* request_queue; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; scalar_t__ mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_queue (struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void scsi_start_queue(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;
	unsigned long flags;

	if (q->mq_ops) {
		blk_mq_unquiesce_queue(q);
	} else {
		spin_lock_irqsave(q->queue_lock, flags);
		blk_start_queue(q);
		spin_unlock_irqrestore(q->queue_lock, flags);
	}
}