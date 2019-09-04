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
struct iscsi_node_attrib {int dataout_timeout; } ;
struct iscsi_conn {struct iscsi_session* sess; } ;
struct iscsi_cmd {int dataout_timer_flags; int /*<<< orphan*/  dataout_timeout_lock; int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  dataout_timer; struct iscsi_conn* conn; } ;

/* Variables and functions */
 int HZ ; 
 int ISCSI_TF_RUNNING ; 
 scalar_t__ get_jiffies_64 () ; 
 struct iscsi_node_attrib* iscsit_tpg_get_node_attrib (struct iscsi_session*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_mod_dataout_timer(struct iscsi_cmd *cmd)
{
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_session *sess = conn->sess;
	struct iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	spin_lock_bh(&cmd->dataout_timeout_lock);
	if (!(cmd->dataout_timer_flags & ISCSI_TF_RUNNING)) {
		spin_unlock_bh(&cmd->dataout_timeout_lock);
		return;
	}

	mod_timer(&cmd->dataout_timer,
		(get_jiffies_64() + na->dataout_timeout * HZ));
	pr_debug("Updated DataOUT timer for ITT: 0x%08x",
			cmd->init_task_tag);
	spin_unlock_bh(&cmd->dataout_timeout_lock);
}