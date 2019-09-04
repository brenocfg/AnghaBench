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
struct se_device {int /*<<< orphan*/  caw_sem; } ;
struct se_cmd {int transport_state; scalar_t__ scsi_status; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  se_cmd_flags; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int CMD_T_SENT ; 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCF_COMPARE_AND_WRITE_POST ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  TCM_NO_SENSE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sense_reason_t compare_and_write_post(struct se_cmd *cmd, bool success,
					     int *post_ret)
{
	struct se_device *dev = cmd->se_dev;
	sense_reason_t ret = TCM_NO_SENSE;

	/*
	 * Only set SCF_COMPARE_AND_WRITE_POST to force a response fall-through
	 * within target_complete_ok_work() if the command was successfully
	 * sent to the backend driver.
	 */
	spin_lock_irq(&cmd->t_state_lock);
	if (cmd->transport_state & CMD_T_SENT) {
		cmd->se_cmd_flags |= SCF_COMPARE_AND_WRITE_POST;
		*post_ret = 1;

		if (cmd->scsi_status == SAM_STAT_CHECK_CONDITION)
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}
	spin_unlock_irq(&cmd->t_state_lock);

	/*
	 * Unlock ->caw_sem originally obtained during sbc_compare_and_write()
	 * before the original READ I/O submission.
	 */
	up(&dev->caw_sem);

	return ret;
}