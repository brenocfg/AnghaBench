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
struct iscsi_session {int dummy; } ;
struct iscsi_conn_recovery {int cmd_count; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_conn_node; struct iscsi_conn_recovery* cr; int /*<<< orphan*/  init_task_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int iscsit_remove_cmd_from_connection_recovery(
	struct iscsi_cmd *cmd,
	struct iscsi_session *sess)
{
	struct iscsi_conn_recovery *cr;

	if (!cmd->cr) {
		pr_err("struct iscsi_conn_recovery pointer for ITT: 0x%08x"
			" is NULL!\n", cmd->init_task_tag);
		BUG();
	}
	cr = cmd->cr;

	list_del_init(&cmd->i_conn_node);
	return --cr->cmd_count;
}