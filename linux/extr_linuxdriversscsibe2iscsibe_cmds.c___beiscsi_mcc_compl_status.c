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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct be_queue_info {int dummy; } ;
struct TYPE_3__ {struct be_queue_info q; } ;
struct TYPE_4__ {int* mcc_tag_status; TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {TYPE_2__ ctrl; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {scalar_t__ va; } ;
struct be_cmd_resp_hdr {int /*<<< orphan*/  actual_resp_len; int /*<<< orphan*/  response_length; } ;
struct be_cmd_req_hdr {int /*<<< orphan*/  opcode; int /*<<< orphan*/  subsystem; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_EH ; 
 int BEISCSI_LOG_INIT ; 
 int CQE_STATUS_ADDL_MASK ; 
 int CQE_STATUS_ADDL_SHIFT ; 
 int CQE_STATUS_MASK ; 
 int CQE_STATUS_WRB_MASK ; 
 int CQE_STATUS_WRB_SHIFT ; 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int MCC_STATUS_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct be_cmd_req_hdr* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ queue_get_wrb (struct be_queue_info*,int) ; 

int __beiscsi_mcc_compl_status(struct beiscsi_hba *phba,
			       unsigned int tag,
			       struct be_mcc_wrb **wrb,
			       struct be_dma_mem *mbx_cmd_mem)
{
	struct be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	uint16_t status = 0, addl_status = 0, wrb_num = 0;
	struct be_cmd_resp_hdr *mbx_resp_hdr;
	struct be_cmd_req_hdr *mbx_hdr;
	struct be_mcc_wrb *temp_wrb;
	uint32_t mcc_tag_status;
	int rc = 0;

	mcc_tag_status = phba->ctrl.mcc_tag_status[tag];
	status = (mcc_tag_status & CQE_STATUS_MASK);
	addl_status = ((mcc_tag_status & CQE_STATUS_ADDL_MASK) >>
			CQE_STATUS_ADDL_SHIFT);

	if (mbx_cmd_mem) {
		mbx_hdr = (struct be_cmd_req_hdr *)mbx_cmd_mem->va;
	} else {
		wrb_num = (mcc_tag_status & CQE_STATUS_WRB_MASK) >>
			  CQE_STATUS_WRB_SHIFT;
		temp_wrb = (struct be_mcc_wrb *)queue_get_wrb(mccq, wrb_num);
		mbx_hdr = embedded_payload(temp_wrb);

		if (wrb)
			*wrb = temp_wrb;
	}

	if (status || addl_status) {
		beiscsi_log(phba, KERN_WARNING,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_EH |
			    BEISCSI_LOG_CONFIG,
			    "BC_%d : MBX Cmd Failed for Subsys : %d Opcode : %d with Status : %d and Extd_Status : %d\n",
			    mbx_hdr->subsystem, mbx_hdr->opcode,
			    status, addl_status);
		rc = -EIO;
		if (status == MCC_STATUS_INSUFFICIENT_BUFFER) {
			mbx_resp_hdr = (struct be_cmd_resp_hdr *)mbx_hdr;
			beiscsi_log(phba, KERN_WARNING,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_EH |
				    BEISCSI_LOG_CONFIG,
				    "BC_%d : Insufficient Buffer Error Resp_Len : %d Actual_Resp_Len : %d\n",
				    mbx_resp_hdr->response_length,
				    mbx_resp_hdr->actual_resp_len);
			rc = -EAGAIN;
		}
	}

	return rc;
}