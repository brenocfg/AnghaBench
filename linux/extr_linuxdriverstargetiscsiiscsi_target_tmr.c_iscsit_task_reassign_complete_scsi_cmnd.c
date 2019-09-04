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
struct iscsi_tmr_req {struct iscsi_cmd* ref_cmd; } ;
struct iscsi_conn_recovery {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  conn_cmd_list; int /*<<< orphan*/  sess; } ;
struct TYPE_2__ {int se_cmd_flags; } ;
struct iscsi_cmd {int init_task_tag; int data_direction; int /*<<< orphan*/  i_state; TYPE_1__ se_cmd; int /*<<< orphan*/  i_conn_node; scalar_t__ exp_stat_sn; scalar_t__ stat_sn; struct iscsi_conn_recovery* cr; } ;

/* Variables and functions */
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  ISTATE_SEND_STATUS ; 
 int SCF_SENT_CHECK_CONDITION ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_task_reassign_complete_none (struct iscsi_cmd*,struct iscsi_tmr_req*) ; 
 int iscsit_task_reassign_complete_read (struct iscsi_cmd*,struct iscsi_tmr_req*) ; 
 int iscsit_task_reassign_complete_write (struct iscsi_cmd*,struct iscsi_tmr_req*) ; 
 int /*<<< orphan*/  iscsit_task_reassign_remove_cmd (struct iscsi_cmd*,struct iscsi_conn_recovery*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_task_reassign_complete_scsi_cmnd(
	struct iscsi_tmr_req *tmr_req,
	struct iscsi_conn *conn)
{
	struct iscsi_cmd *cmd = tmr_req->ref_cmd;
	struct iscsi_conn_recovery *cr;

	if (!cmd->cr) {
		pr_err("struct iscsi_conn_recovery pointer for ITT: 0x%08x"
			" is NULL!\n", cmd->init_task_tag);
		return -1;
	}
	cr = cmd->cr;

	/*
	 * Reset the StatSN so a new one for this commands new connection
	 * will be assigned.
	 * Reset the ExpStatSN as well so we may receive Status SNACKs.
	 */
	cmd->stat_sn = cmd->exp_stat_sn = 0;

	iscsit_task_reassign_remove_cmd(cmd, cr, conn->sess);

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	if (cmd->se_cmd.se_cmd_flags & SCF_SENT_CHECK_CONDITION) {
		cmd->i_state = ISTATE_SEND_STATUS;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		return 0;
	}

	switch (cmd->data_direction) {
	case DMA_TO_DEVICE:
		return iscsit_task_reassign_complete_write(cmd, tmr_req);
	case DMA_FROM_DEVICE:
		return iscsit_task_reassign_complete_read(cmd, tmr_req);
	case DMA_NONE:
		return iscsit_task_reassign_complete_none(cmd, tmr_req);
	default:
		pr_err("Unknown cmd->data_direction: 0x%02x\n",
				cmd->data_direction);
		return -1;
	}

	return 0;
}