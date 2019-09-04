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
struct iscsi_tmr_req {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_state; struct iscsi_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISTATE_SEND_STATUS ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_task_reassign_complete_none(
	struct iscsi_cmd *cmd,
	struct iscsi_tmr_req *tmr_req)
{
	struct iscsi_conn *conn = cmd->conn;

	cmd->i_state = ISTATE_SEND_STATUS;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	return 0;
}