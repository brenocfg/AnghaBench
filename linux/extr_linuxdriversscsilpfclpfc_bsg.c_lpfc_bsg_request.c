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
typedef  int uint32_t ;
struct fc_bsg_request {int msgcode; } ;
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct bsg_job {struct fc_bsg_reply* reply; struct fc_bsg_request* request; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FC_BSG_HST_VENDOR 130 
#define  FC_BSG_RPT_CT 129 
#define  FC_BSG_RPT_ELS 128 
 int lpfc_bsg_hst_vendor (struct bsg_job*) ; 
 int lpfc_bsg_rport_els (struct bsg_job*) ; 
 int lpfc_bsg_send_mgmt_cmd (struct bsg_job*) ; 

int
lpfc_bsg_request(struct bsg_job *job)
{
	struct fc_bsg_request *bsg_request = job->request;
	struct fc_bsg_reply *bsg_reply = job->reply;
	uint32_t msgcode;
	int rc;

	msgcode = bsg_request->msgcode;
	switch (msgcode) {
	case FC_BSG_HST_VENDOR:
		rc = lpfc_bsg_hst_vendor(job);
		break;
	case FC_BSG_RPT_ELS:
		rc = lpfc_bsg_rport_els(job);
		break;
	case FC_BSG_RPT_CT:
		rc = lpfc_bsg_send_mgmt_cmd(job);
		break;
	default:
		rc = -EINVAL;
		bsg_reply->reply_payload_rcv_len = 0;
		/* make error code available to userspace */
		bsg_reply->result = rc;
		break;
	}

	return rc;
}