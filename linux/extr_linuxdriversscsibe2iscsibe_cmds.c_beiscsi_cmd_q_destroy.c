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
typedef  int /*<<< orphan*/  u8 ;
struct beiscsi_hba {int dummy; } ;
struct be_queue_info {int /*<<< orphan*/  id; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  pdev; int /*<<< orphan*/  mbox_mem; } ;
struct be_cmd_req_q_destroy {int /*<<< orphan*/  id; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_COMMON_CQ_DESTROY ; 
 int /*<<< orphan*/  OPCODE_COMMON_EQ_DESTROY ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_CFG_REMOVE_SGL_PAGES ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_DEFQ_DESTROY ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_WRBQ_DESTROY ; 
 int /*<<< orphan*/  OPCODE_COMMON_MCC_DESTROY ; 
#define  QTYPE_CQ 133 
#define  QTYPE_DPDUQ 132 
#define  QTYPE_EQ 131 
#define  QTYPE_MCCQ 130 
#define  QTYPE_SGL 129 
#define  QTYPE_WRBQ 128 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct be_cmd_req_q_destroy* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct beiscsi_hba* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_cmd_q_destroy(struct be_ctrl_info *ctrl, struct be_queue_info *q,
			  int queue_type)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct be_cmd_req_q_destroy *req = embedded_payload(wrb);
	struct beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	u8 subsys = 0, opcode = 0;
	int status;

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BC_%d : In beiscsi_cmd_q_destroy "
		    "queue_type : %d\n", queue_type);

	mutex_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));
	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);

	switch (queue_type) {
	case QTYPE_EQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_EQ_DESTROY;
		break;
	case QTYPE_CQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_CQ_DESTROY;
		break;
	case QTYPE_MCCQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_MCC_DESTROY;
		break;
	case QTYPE_WRBQ:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_WRBQ_DESTROY;
		break;
	case QTYPE_DPDUQ:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_DEFQ_DESTROY;
		break;
	case QTYPE_SGL:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_CFG_REMOVE_SGL_PAGES;
		break;
	default:
		mutex_unlock(&ctrl->mbox_lock);
		BUG();
	}
	be_cmd_hdr_prepare(&req->hdr, subsys, opcode, sizeof(*req));
	if (queue_type != QTYPE_SGL)
		req->id = cpu_to_le16(q->id);

	status = be_mbox_notify(ctrl);

	mutex_unlock(&ctrl->mbox_lock);
	return status;
}