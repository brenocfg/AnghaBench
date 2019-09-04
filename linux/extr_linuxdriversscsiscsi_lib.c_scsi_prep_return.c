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
struct scsi_device {int /*<<< orphan*/  device_busy; int /*<<< orphan*/  sdev_gendev; } ;
struct scsi_cmnd {int dummy; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct request {int /*<<< orphan*/  rq_flags; struct scsi_cmnd* special; } ;
struct TYPE_2__ {int result; } ;

/* Variables and functions */
#define  BLKPREP_DEFER 130 
#define  BLKPREP_INVALID 129 
#define  BLKPREP_KILL 128 
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  RQF_DONTPREP ; 
 int /*<<< orphan*/  SCSI_QUEUE_DELAY ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_delay_queue (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_put_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_release_buffers (struct scsi_cmnd*) ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static int
scsi_prep_return(struct request_queue *q, struct request *req, int ret)
{
	struct scsi_device *sdev = q->queuedata;

	switch (ret) {
	case BLKPREP_KILL:
	case BLKPREP_INVALID:
		scsi_req(req)->result = DID_NO_CONNECT << 16;
		/* release the command and kill it */
		if (req->special) {
			struct scsi_cmnd *cmd = req->special;
			scsi_release_buffers(cmd);
			scsi_put_command(cmd);
			put_device(&sdev->sdev_gendev);
			req->special = NULL;
		}
		break;
	case BLKPREP_DEFER:
		/*
		 * If we defer, the blk_peek_request() returns NULL, but the
		 * queue must be restarted, so we schedule a callback to happen
		 * shortly.
		 */
		if (atomic_read(&sdev->device_busy) == 0)
			blk_delay_queue(q, SCSI_QUEUE_DELAY);
		break;
	default:
		req->rq_flags |= RQF_DONTPREP;
	}

	return ret;
}