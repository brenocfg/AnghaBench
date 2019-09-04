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
struct se_cmd {int transport_state; int se_cmd_flags; TYPE_1__* se_tfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* aborted_task ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int CMD_T_TAS ; 
 int SCF_ACK_KREF ; 
 int SCF_SE_LUN_CMD ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int target_put_sess_cmd (struct se_cmd*) ; 
 scalar_t__ transport_cmd_check_stop_to_fabric (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_lun_remove_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_send_task_abort (struct se_cmd*) ; 

int transport_cmd_finish_abort(struct se_cmd *cmd)
{
	bool send_tas = cmd->transport_state & CMD_T_TAS;
	bool ack_kref = (cmd->se_cmd_flags & SCF_ACK_KREF);
	int ret = 0;

	if (send_tas)
		transport_send_task_abort(cmd);

	if (cmd->se_cmd_flags & SCF_SE_LUN_CMD)
		transport_lun_remove_cmd(cmd);
	/*
	 * Allow the fabric driver to unmap any resources before
	 * releasing the descriptor via TFO->release_cmd()
	 */
	if (!send_tas)
		cmd->se_tfo->aborted_task(cmd);

	if (transport_cmd_check_stop_to_fabric(cmd))
		return 1;
	if (!send_tas && ack_kref)
		ret = target_put_sess_cmd(cmd);

	return ret;
}