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
struct scsi_device {struct request_queue* request_queue; TYPE_1__* host; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct TYPE_2__ {int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_SCSI_PASSTHROUGH ; 
 int /*<<< orphan*/  __scsi_init_queue (TYPE_1__*,struct request_queue*) ; 
 struct request_queue* blk_mq_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 

struct request_queue *scsi_mq_alloc_queue(struct scsi_device *sdev)
{
	sdev->request_queue = blk_mq_init_queue(&sdev->host->tag_set);
	if (IS_ERR(sdev->request_queue))
		return NULL;

	sdev->request_queue->queuedata = sdev;
	__scsi_init_queue(sdev->host, sdev->request_queue);
	blk_queue_flag_set(QUEUE_FLAG_SCSI_PASSTHROUGH, sdev->request_queue);
	return sdev->request_queue;
}