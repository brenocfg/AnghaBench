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
struct iscsi_tmr_req {struct iscsi_cmd* ref_cmd; } ;
struct iscsi_conn {int /*<<< orphan*/  cid; } ;
struct iscsi_cmd {int iscsi_opcode; int /*<<< orphan*/  init_task_tag; struct iscsi_conn* conn; } ;

/* Variables and functions */
#define  ISCSI_OP_NOOP_OUT 129 
#define  ISCSI_OP_SCSI_CMD 128 
 int iscsit_task_reassign_complete_nop_out (struct iscsi_tmr_req*,struct iscsi_conn*) ; 
 int iscsit_task_reassign_complete_scsi_cmnd (struct iscsi_tmr_req*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int iscsit_task_reassign_complete(
	struct iscsi_tmr_req *tmr_req,
	struct iscsi_conn *conn)
{
	struct iscsi_cmd *cmd;
	int ret = 0;

	if (!tmr_req->ref_cmd) {
		pr_err("TMR Request is missing a RefCmd struct iscsi_cmd.\n");
		return -1;
	}
	cmd = tmr_req->ref_cmd;

	cmd->conn = conn;

	switch (cmd->iscsi_opcode) {
	case ISCSI_OP_NOOP_OUT:
		ret = iscsit_task_reassign_complete_nop_out(tmr_req, conn);
		break;
	case ISCSI_OP_SCSI_CMD:
		ret = iscsit_task_reassign_complete_scsi_cmnd(tmr_req, conn);
		break;
	default:
		 pr_err("Illegal iSCSI Opcode 0x%02x during"
			" command reallegiance\n", cmd->iscsi_opcode);
		return -1;
	}

	if (ret != 0)
		return ret;

	pr_debug("Completed connection reallegiance for Opcode: 0x%02x,"
		" ITT: 0x%08x to CID: %hu.\n", cmd->iscsi_opcode,
			cmd->init_task_tag, conn->cid);

	return 0;
}