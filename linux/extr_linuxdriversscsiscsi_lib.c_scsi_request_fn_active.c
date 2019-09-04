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
struct scsi_device {TYPE_1__* host; struct request_queue* request_queue; } ;
struct request_queue {int request_fn_active; int /*<<< orphan*/  queue_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_blk_mq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsi_request_fn_active(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;
	int request_fn_active;

	WARN_ON_ONCE(sdev->host->use_blk_mq);

	spin_lock_irq(q->queue_lock);
	request_fn_active = q->request_fn_active;
	spin_unlock_irq(q->queue_lock);

	return request_fn_active;
}