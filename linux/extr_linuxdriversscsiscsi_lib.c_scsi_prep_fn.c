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
struct scsi_cmnd {int /*<<< orphan*/  prot_op; struct request* request; int /*<<< orphan*/  tag; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct request {int /*<<< orphan*/  tag; struct scsi_cmnd* special; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  SCSI_PROT_NORMAL ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_init_command (struct scsi_device*,struct scsi_cmnd*) ; 
 int scsi_prep_return (struct request_queue*,struct request*,int) ; 
 int scsi_prep_state_check (struct scsi_device*,struct request*) ; 
 int scsi_setup_cmnd (struct scsi_device*,struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int scsi_prep_fn(struct request_queue *q, struct request *req)
{
	struct scsi_device *sdev = q->queuedata;
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	int ret;

	ret = scsi_prep_state_check(sdev, req);
	if (ret != BLKPREP_OK)
		goto out;

	if (!req->special) {
		/* Bail if we can't get a reference to the device */
		if (unlikely(!get_device(&sdev->sdev_gendev))) {
			ret = BLKPREP_DEFER;
			goto out;
		}

		scsi_init_command(sdev, cmd);
		req->special = cmd;
	}

	cmd->tag = req->tag;
	cmd->request = req;
	cmd->prot_op = SCSI_PROT_NORMAL;

	ret = scsi_setup_cmnd(sdev, req);
out:
	return scsi_prep_return(q, req, ret);
}