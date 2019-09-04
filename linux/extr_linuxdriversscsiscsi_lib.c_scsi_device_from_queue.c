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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct request_queue {scalar_t__ request_fn; struct scsi_device* queuedata; int /*<<< orphan*/ * mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_mq_ops ; 
 scalar_t__ scsi_request_fn ; 

struct scsi_device *scsi_device_from_queue(struct request_queue *q)
{
	struct scsi_device *sdev = NULL;

	if (q->mq_ops) {
		if (q->mq_ops == &scsi_mq_ops)
			sdev = q->queuedata;
	} else if (q->request_fn == scsi_request_fn)
		sdev = q->queuedata;
	if (!sdev || !get_device(&sdev->sdev_gendev))
		sdev = NULL;

	return sdev;
}