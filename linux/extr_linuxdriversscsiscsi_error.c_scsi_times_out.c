#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* device; } ;
struct request {TYPE_2__* q; } ;
struct Scsi_Host {int eh_deadline; TYPE_1__* hostt; scalar_t__ last_reset; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_6__ {struct Scsi_Host* host; } ;
struct TYPE_5__ {scalar_t__ mq_ops; } ;
struct TYPE_4__ {int (* eh_timed_out ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int /*<<< orphan*/  DID_TIME_OUT ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  TIMEOUT_ERROR ; 
 int /*<<< orphan*/  blk_mq_mark_complete (struct request*) ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ scsi_abort_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_scmd_add (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_log_completion (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  trace_scsi_dispatch_cmd_timeout (struct scsi_cmnd*) ; 

enum blk_eh_timer_return scsi_times_out(struct request *req)
{
	struct scsi_cmnd *scmd = blk_mq_rq_to_pdu(req);
	enum blk_eh_timer_return rtn = BLK_EH_DONE;
	struct Scsi_Host *host = scmd->device->host;

	trace_scsi_dispatch_cmd_timeout(scmd);
	scsi_log_completion(scmd, TIMEOUT_ERROR);

	if (host->eh_deadline != -1 && !host->last_reset)
		host->last_reset = jiffies;

	if (host->hostt->eh_timed_out)
		rtn = host->hostt->eh_timed_out(scmd);

	if (rtn == BLK_EH_DONE) {
		/*
		 * For blk-mq, we must set the request state to complete now
		 * before sending the request to the scsi error handler. This
		 * will prevent a use-after-free in the event the LLD manages
		 * to complete the request before the error handler finishes
		 * processing this timed out request.
		 *
		 * If the request was already completed, then the LLD beat the
		 * time out handler from transferring the request to the scsi
		 * error handler. In that case we can return immediately as no
		 * further action is required.
		 */
		if (req->q->mq_ops && !blk_mq_mark_complete(req))
			return rtn;
		if (scsi_abort_command(scmd) != SUCCESS) {
			set_host_byte(scmd, DID_TIME_OUT);
			scsi_eh_scmd_add(scmd);
		}
	}

	return rtn;
}