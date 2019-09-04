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
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_state; int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iscsit_queue_rsp(struct iscsi_conn *conn, struct iscsi_cmd *cmd)
{
	return iscsit_add_cmd_to_response_queue(cmd, cmd->conn, cmd->i_state);
}