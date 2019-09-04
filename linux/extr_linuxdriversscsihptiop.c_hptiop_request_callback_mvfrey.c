#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hptiop_hba {int msg_done; TYPE_1__* reqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  result; } ;
struct hpt_iop_request_scsi_command {TYPE_2__ header; } ;
struct TYPE_3__ {struct hpt_iop_request_scsi_command* req_virt; } ;

/* Variables and functions */
 int IOPMU_QUEUE_REQUEST_RESULT_BIT ; 
#define  IOP_REQUEST_TYPE_GET_CONFIG 130 
#define  IOP_REQUEST_TYPE_SCSI_COMMAND 129 
#define  IOP_REQUEST_TYPE_SET_CONFIG 128 
 int /*<<< orphan*/  IOP_RESULT_SUCCESS ; 
 int /*<<< orphan*/  hptiop_finish_scsi_req (struct hptiop_hba*,int,struct hpt_iop_request_scsi_command*) ; 
 int /*<<< orphan*/  likely (int) ; 

__attribute__((used)) static void hptiop_request_callback_mvfrey(struct hptiop_hba *hba, u32 _tag)
{
	u32 req_type = _tag & 0xf;
	struct hpt_iop_request_scsi_command *req;

	switch (req_type) {
	case IOP_REQUEST_TYPE_GET_CONFIG:
	case IOP_REQUEST_TYPE_SET_CONFIG:
		hba->msg_done = 1;
		break;

	case IOP_REQUEST_TYPE_SCSI_COMMAND:
		req = hba->reqs[(_tag >> 4) & 0xff].req_virt;
		if (likely(_tag & IOPMU_QUEUE_REQUEST_RESULT_BIT))
			req->header.result = IOP_RESULT_SUCCESS;
		hptiop_finish_scsi_req(hba, (_tag >> 4) & 0xff, req);
		break;

	default:
		break;
	}
}