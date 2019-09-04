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
struct iscsi_session {TYPE_1__* sess_ops; } ;
struct iscsi_conn {scalar_t__ cid; struct iscsi_session* sess; } ;
struct iscsi_cmd {scalar_t__ logout_cid; int /*<<< orphan*/  i_state; int /*<<< orphan*/  logout_response; } ;
struct TYPE_2__ {int ErrorRecoveryLevel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_LOGOUT_CLEANUP_FAILED ; 
 int /*<<< orphan*/  ISCSI_LOGOUT_RECOVERY_UNSUPPORTED ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int iscsit_logout_removeconnforrecovery(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	struct iscsi_session *sess = conn->sess;

	pr_debug("Received explicit REMOVECONNFORRECOVERY logout for"
		" CID: %hu on CID: %hu.\n", cmd->logout_cid, conn->cid);

	if (sess->sess_ops->ErrorRecoveryLevel != 2) {
		pr_err("Received Logout Request REMOVECONNFORRECOVERY"
			" while ERL!=2.\n");
		cmd->logout_response = ISCSI_LOGOUT_RECOVERY_UNSUPPORTED;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		return 0;
	}

	if (conn->cid == cmd->logout_cid) {
		pr_err("Received Logout Request REMOVECONNFORRECOVERY"
			" with CID: %hu on CID: %hu, implementation error.\n",
				cmd->logout_cid, conn->cid);
		cmd->logout_response = ISCSI_LOGOUT_CLEANUP_FAILED;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		return 0;
	}

	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);

	return 0;
}