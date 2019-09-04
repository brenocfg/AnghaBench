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
typedef  scalar_t__ u32 ;
struct se_cmd {int transport_state; scalar_t__ data_length; int /*<<< orphan*/  t_state; } ;
struct iscsi_tmr_req {scalar_t__ exp_data_sn; } ;
struct iscsi_conn {TYPE_3__* conn_transport; TYPE_2__* sess; } ;
struct iscsi_cmd {int cmd_flags; scalar_t__ next_burst_len; scalar_t__ write_data_done; int /*<<< orphan*/  r2t_lock; int /*<<< orphan*/  outstanding_r2ts; struct se_cmd se_cmd; scalar_t__ unsolicited_data; int /*<<< orphan*/  i_state; int /*<<< orphan*/  init_task_tag; scalar_t__ acked_data_sn; struct iscsi_conn* conn; } ;
struct TYPE_6__ {int (* iscsit_get_dataout ) (struct iscsi_conn*,struct iscsi_cmd*,int) ;} ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {scalar_t__ FirstBurstLength; } ;

/* Variables and functions */
 int CMD_T_SENT ; 
 int ICF_GOT_DATACK_SNACK ; 
 int ICF_GOT_LAST_DATAOUT ; 
 int /*<<< orphan*/  ISTATE_SEND_STATUS ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ iscsit_add_r2t_to_list (struct iscsi_cmd*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct iscsi_conn*,struct iscsi_cmd*,int) ; 
 int /*<<< orphan*/  target_execute_cmd (struct se_cmd*) ; 

__attribute__((used)) static int iscsit_task_reassign_complete_write(
	struct iscsi_cmd *cmd,
	struct iscsi_tmr_req *tmr_req)
{
	int no_build_r2ts = 0;
	u32 length = 0, offset = 0;
	struct iscsi_conn *conn = cmd->conn;
	struct se_cmd *se_cmd = &cmd->se_cmd;
	/*
	 * The Initiator must not send a R2T SNACK with a Begrun less than
	 * the TMR TASK_REASSIGN's ExpDataSN.
	 */
	if (!tmr_req->exp_data_sn) {
		cmd->cmd_flags &= ~ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = 0;
	} else {
		cmd->cmd_flags |= ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = (tmr_req->exp_data_sn - 1);
	}

	/*
	 * The TMR TASK_REASSIGN's ExpDataSN contains the next R2TSN the
	 * Initiator is expecting.  The Target controls all WRITE operations
	 * so if we have received all DataOUT we can safety ignore Initiator.
	 */
	if (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT) {
		if (!(cmd->se_cmd.transport_state & CMD_T_SENT)) {
			pr_debug("WRITE ITT: 0x%08x: t_state: %d"
				" never sent to transport\n",
				cmd->init_task_tag, cmd->se_cmd.t_state);
			target_execute_cmd(se_cmd);
			return 0;
		}

		cmd->i_state = ISTATE_SEND_STATUS;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		return 0;
	}

	/*
	 * Special case to deal with DataSequenceInOrder=No and Non-Immeidate
	 * Unsolicited DataOut.
	 */
	if (cmd->unsolicited_data) {
		cmd->unsolicited_data = 0;

		offset = cmd->next_burst_len = cmd->write_data_done;

		if ((conn->sess->sess_ops->FirstBurstLength - offset) >=
		     cmd->se_cmd.data_length) {
			no_build_r2ts = 1;
			length = (cmd->se_cmd.data_length - offset);
		} else
			length = (conn->sess->sess_ops->FirstBurstLength - offset);

		spin_lock_bh(&cmd->r2t_lock);
		if (iscsit_add_r2t_to_list(cmd, offset, length, 0, 0) < 0) {
			spin_unlock_bh(&cmd->r2t_lock);
			return -1;
		}
		cmd->outstanding_r2ts++;
		spin_unlock_bh(&cmd->r2t_lock);

		if (no_build_r2ts)
			return 0;
	}
	/*
	 * iscsit_build_r2ts_for_cmd() can handle the rest from here.
	 */
	return conn->conn_transport->iscsit_get_dataout(conn, cmd, true);
}