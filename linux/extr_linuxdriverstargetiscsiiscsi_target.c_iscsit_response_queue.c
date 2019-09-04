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
struct iscsi_conn {int /*<<< orphan*/  check_immediate_queue; int /*<<< orphan*/  cid; int /*<<< orphan*/  sess; } ;
struct iscsi_cmd {int i_state; int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  iscsi_opcode; int /*<<< orphan*/  istate_lock; } ;

/* Variables and functions */
 int ECONNRESET ; 
#define  ISTATE_SEND_ASYNCMSG 136 
#define  ISTATE_SEND_DATAIN 135 
#define  ISTATE_SEND_LOGOUTRSP 134 
#define  ISTATE_SEND_NOPIN 133 
#define  ISTATE_SEND_REJECT 132 
#define  ISTATE_SEND_STATUS 131 
#define  ISTATE_SEND_STATUS_RECOVERY 130 
#define  ISTATE_SEND_TASKMGTRSP 129 
#define  ISTATE_SEND_TEXTRSP 128 
 void* ISTATE_SENT_STATUS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_fall_back_to_erl0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_logout_post_handler (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_conn_drop_async_message (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_datain (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_logout (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_nopin (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_reject (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_response (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_task_mgt_rsp (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_text_rsp (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_tmr_post_handler (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int
iscsit_response_queue(struct iscsi_conn *conn, struct iscsi_cmd *cmd, int state)
{
	int ret;

check_rsp_state:
	switch (state) {
	case ISTATE_SEND_DATAIN:
		ret = iscsit_send_datain(cmd, conn);
		if (ret < 0)
			goto err;
		else if (!ret)
			/* more drs */
			goto check_rsp_state;
		else if (ret == 1) {
			/* all done */
			spin_lock_bh(&cmd->istate_lock);
			cmd->i_state = ISTATE_SENT_STATUS;
			spin_unlock_bh(&cmd->istate_lock);

			if (atomic_read(&conn->check_immediate_queue))
				return 1;

			return 0;
		} else if (ret == 2) {
			/* Still must send status,
			   SCF_TRANSPORT_TASK_SENSE was set */
			spin_lock_bh(&cmd->istate_lock);
			cmd->i_state = ISTATE_SEND_STATUS;
			spin_unlock_bh(&cmd->istate_lock);
			state = ISTATE_SEND_STATUS;
			goto check_rsp_state;
		}

		break;
	case ISTATE_SEND_STATUS:
	case ISTATE_SEND_STATUS_RECOVERY:
		ret = iscsit_send_response(cmd, conn);
		break;
	case ISTATE_SEND_LOGOUTRSP:
		ret = iscsit_send_logout(cmd, conn);
		break;
	case ISTATE_SEND_ASYNCMSG:
		ret = iscsit_send_conn_drop_async_message(
			cmd, conn);
		break;
	case ISTATE_SEND_NOPIN:
		ret = iscsit_send_nopin(cmd, conn);
		break;
	case ISTATE_SEND_REJECT:
		ret = iscsit_send_reject(cmd, conn);
		break;
	case ISTATE_SEND_TASKMGTRSP:
		ret = iscsit_send_task_mgt_rsp(cmd, conn);
		if (ret != 0)
			break;
		ret = iscsit_tmr_post_handler(cmd, conn);
		if (ret != 0)
			iscsit_fall_back_to_erl0(conn->sess);
		break;
	case ISTATE_SEND_TEXTRSP:
		ret = iscsit_send_text_rsp(cmd, conn);
		break;
	default:
		pr_err("Unknown Opcode: 0x%02x ITT:"
		       " 0x%08x, i_state: %d on CID: %hu\n",
		       cmd->iscsi_opcode, cmd->init_task_tag,
		       state, conn->cid);
		goto err;
	}
	if (ret < 0)
		goto err;

	switch (state) {
	case ISTATE_SEND_LOGOUTRSP:
		if (!iscsit_logout_post_handler(cmd, conn))
			return -ECONNRESET;
		/* fall through */
	case ISTATE_SEND_STATUS:
	case ISTATE_SEND_ASYNCMSG:
	case ISTATE_SEND_NOPIN:
	case ISTATE_SEND_STATUS_RECOVERY:
	case ISTATE_SEND_TEXTRSP:
	case ISTATE_SEND_TASKMGTRSP:
	case ISTATE_SEND_REJECT:
		spin_lock_bh(&cmd->istate_lock);
		cmd->i_state = ISTATE_SENT_STATUS;
		spin_unlock_bh(&cmd->istate_lock);
		break;
	default:
		pr_err("Unknown Opcode: 0x%02x ITT:"
		       " 0x%08x, i_state: %d on CID: %hu\n",
		       cmd->iscsi_opcode, cmd->init_task_tag,
		       cmd->i_state, conn->cid);
		goto err;
	}

	if (atomic_read(&conn->check_immediate_queue))
		return 1;

	return 0;

err:
	return -1;
}