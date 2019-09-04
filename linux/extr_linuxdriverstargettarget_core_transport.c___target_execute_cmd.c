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
struct se_cmd {int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  transport_state; scalar_t__ (* execute_cmd ) (struct se_cmd*) ;int /*<<< orphan*/  scsi_status; } ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_T_SENT ; 
 int /*<<< orphan*/  SAM_STAT_RESERVATION_CONFLICT ; 
 scalar_t__ TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct se_cmd*) ; 
 scalar_t__ target_alua_state_check (struct se_cmd*) ; 
 scalar_t__ target_check_reservation (struct se_cmd*) ; 
 scalar_t__ target_scsi3_ua_check (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_generic_request_failure (struct se_cmd*,scalar_t__) ; 

void __target_execute_cmd(struct se_cmd *cmd, bool do_checks)
{
	sense_reason_t ret;

	if (!cmd->execute_cmd) {
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		goto err;
	}
	if (do_checks) {
		/*
		 * Check for an existing UNIT ATTENTION condition after
		 * target_handle_task_attr() has done SAM task attr
		 * checking, and possibly have already defered execution
		 * out to target_restart_delayed_cmds() context.
		 */
		ret = target_scsi3_ua_check(cmd);
		if (ret)
			goto err;

		ret = target_alua_state_check(cmd);
		if (ret)
			goto err;

		ret = target_check_reservation(cmd);
		if (ret) {
			cmd->scsi_status = SAM_STAT_RESERVATION_CONFLICT;
			goto err;
		}
	}

	ret = cmd->execute_cmd(cmd);
	if (!ret)
		return;
err:
	spin_lock_irq(&cmd->t_state_lock);
	cmd->transport_state &= ~CMD_T_SENT;
	spin_unlock_irq(&cmd->t_state_lock);

	transport_generic_request_failure(cmd, ret);
}