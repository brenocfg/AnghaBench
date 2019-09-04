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
typedef  int /*<<< orphan*/  uint32_t ;
struct fc_internal {TYPE_3__* f; } ;
struct fc_bsg_rport_els {int dummy; } ;
struct fc_bsg_rport_ct {int dummy; } ;
struct fc_bsg_request {int msgcode; } ;
struct fc_bsg_reply {int result; scalar_t__ reply_payload_rcv_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  payload_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  payload_len; } ;
struct bsg_job {int request_len; int reply_len; TYPE_2__ reply_payload; TYPE_1__ request_payload; struct fc_bsg_reply* reply; struct fc_bsg_request* request; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bsg_request ) (struct bsg_job*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBADR ; 
 int EINVAL ; 
 int ENOMSG ; 
#define  FC_BSG_RPT_CT 129 
#define  FC_BSG_RPT_ELS 128 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct bsg_job*) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_bsg_rport_dispatch(struct Scsi_Host *shost, struct bsg_job *job)
{
	struct fc_internal *i = to_fc_internal(shost->transportt);
	struct fc_bsg_request *bsg_request = job->request;
	struct fc_bsg_reply *bsg_reply = job->reply;
	int cmdlen = sizeof(uint32_t);	/* start with length of msgcode */
	int ret;

	/* check if we really have all the request data needed */
	if (job->request_len < cmdlen) {
		ret = -ENOMSG;
		goto fail_rport_msg;
	}

	/* Validate the rport command */
	switch (bsg_request->msgcode) {
	case FC_BSG_RPT_ELS:
		cmdlen += sizeof(struct fc_bsg_rport_els);
		goto check_bidi;

	case FC_BSG_RPT_CT:
		cmdlen += sizeof(struct fc_bsg_rport_ct);
check_bidi:
		/* there better be xmt and rcv payloads */
		if ((!job->request_payload.payload_len) ||
		    (!job->reply_payload.payload_len)) {
			ret = -EINVAL;
			goto fail_rport_msg;
		}
		break;
	default:
		ret = -EBADR;
		goto fail_rport_msg;
	}

	ret = i->f->bsg_request(job);
	if (!ret)
		return 0;

fail_rport_msg:
	/* return the errno failure code as the only status */
	BUG_ON(job->reply_len < sizeof(uint32_t));
	bsg_reply->reply_payload_rcv_len = 0;
	bsg_reply->result = ret;
	job->reply_len = sizeof(uint32_t);
	bsg_job_done(job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	return 0;
}