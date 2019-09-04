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
typedef  int u8 ;
struct se_device {int /*<<< orphan*/  caw_sem; } ;
struct se_cmd {int scsi_status; int se_cmd_flags; int transport_state; int /*<<< orphan*/  work; int /*<<< orphan*/  cpuid; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_state; int /*<<< orphan*/  t_transport_stop_comp; struct se_device* se_dev; } ;

/* Variables and functions */
 int CMD_T_ABORTED ; 
 int CMD_T_ACTIVE ; 
 int CMD_T_COMPLETE ; 
 int CMD_T_STOP ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SAM_STAT_CHECK_CONDITION 128 
 int SCF_COMPARE_AND_WRITE ; 
 int SCF_TRANSPORT_TASK_SENSE ; 
 int SCF_USE_CPUID ; 
 int /*<<< orphan*/  TRANSPORT_COMPLETE ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  target_complete_failure_work ; 
 int /*<<< orphan*/  target_complete_ok_work ; 
 int /*<<< orphan*/  target_completion_wq ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void target_complete_cmd(struct se_cmd *cmd, u8 scsi_status)
{
	struct se_device *dev = cmd->se_dev;
	int success;
	unsigned long flags;

	cmd->scsi_status = scsi_status;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	switch (cmd->scsi_status) {
	case SAM_STAT_CHECK_CONDITION:
		if (cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE)
			success = 1;
		else
			success = 0;
		break;
	default:
		success = 1;
		break;
	}

	/*
	 * Check for case where an explicit ABORT_TASK has been received
	 * and transport_wait_for_tasks() will be waiting for completion..
	 */
	if (cmd->transport_state & CMD_T_ABORTED ||
	    cmd->transport_state & CMD_T_STOP) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		/*
		 * If COMPARE_AND_WRITE was stopped by __transport_wait_for_tasks(),
		 * release se_device->caw_sem obtained by sbc_compare_and_write()
		 * since target_complete_ok_work() or target_complete_failure_work()
		 * won't be called to invoke the normal CAW completion callbacks.
		 */
		if (cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE) {
			up(&dev->caw_sem);
		}
		complete_all(&cmd->t_transport_stop_comp);
		return;
	} else if (!success) {
		INIT_WORK(&cmd->work, target_complete_failure_work);
	} else {
		INIT_WORK(&cmd->work, target_complete_ok_work);
	}

	cmd->t_state = TRANSPORT_COMPLETE;
	cmd->transport_state |= (CMD_T_COMPLETE | CMD_T_ACTIVE);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	if (cmd->se_cmd_flags & SCF_USE_CPUID)
		queue_work_on(cmd->cpuid, target_completion_wq, &cmd->work);
	else
		queue_work(target_completion_wq, &cmd->work);
}