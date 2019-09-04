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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_sense_hdr {int dummy; } ;
struct scsi_request {unsigned char* cmd; int retries; unsigned int resid_len; unsigned char const* sense; int result; scalar_t__ sense_len; int /*<<< orphan*/  cmd_len; } ;
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct request {int timeout; int rq_flags; int /*<<< orphan*/  q; int /*<<< orphan*/  cmd_flags; } ;
typedef  int req_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_PREEMPT ; 
 int /*<<< orphan*/  COMMAND_SIZE (unsigned char const) ; 
 int DMA_TO_DEVICE ; 
 int DRIVER_ERROR ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_SCSI_IN ; 
 int /*<<< orphan*/  REQ_OP_SCSI_OUT ; 
 int RQF_QUIET ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scsi_normalize_sense (unsigned char const*,scalar_t__,struct scsi_sense_hdr*) ; 
 struct scsi_request* scsi_req (struct request*) ; 
 scalar_t__ unlikely (int) ; 

int __scsi_execute(struct scsi_device *sdev, const unsigned char *cmd,
		 int data_direction, void *buffer, unsigned bufflen,
		 unsigned char *sense, struct scsi_sense_hdr *sshdr,
		 int timeout, int retries, u64 flags, req_flags_t rq_flags,
		 int *resid)
{
	struct request *req;
	struct scsi_request *rq;
	int ret = DRIVER_ERROR << 24;

	req = blk_get_request(sdev->request_queue,
			data_direction == DMA_TO_DEVICE ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, BLK_MQ_REQ_PREEMPT);
	if (IS_ERR(req))
		return ret;
	rq = scsi_req(req);

	if (bufflen &&	blk_rq_map_kern(sdev->request_queue, req,
					buffer, bufflen, GFP_NOIO))
		goto out;

	rq->cmd_len = COMMAND_SIZE(cmd[0]);
	memcpy(rq->cmd, cmd, rq->cmd_len);
	rq->retries = retries;
	req->timeout = timeout;
	req->cmd_flags |= flags;
	req->rq_flags |= rq_flags | RQF_QUIET;

	/*
	 * head injection *required* here otherwise quiesce won't work
	 */
	blk_execute_rq(req->q, NULL, req, 1);

	/*
	 * Some devices (USB mass-storage in particular) may transfer
	 * garbage data together with a residue indicating that the data
	 * is invalid.  Prevent the garbage from being misinterpreted
	 * and prevent security leaks by zeroing out the excess data.
	 */
	if (unlikely(rq->resid_len > 0 && rq->resid_len <= bufflen))
		memset(buffer + (bufflen - rq->resid_len), 0, rq->resid_len);

	if (resid)
		*resid = rq->resid_len;
	if (sense && rq->sense_len)
		memcpy(sense, rq->sense, SCSI_SENSE_BUFFERSIZE);
	if (sshdr)
		scsi_normalize_sense(rq->sense, rq->sense_len, sshdr);
	ret = rq->result;
 out:
	blk_put_request(req);

	return ret;
}