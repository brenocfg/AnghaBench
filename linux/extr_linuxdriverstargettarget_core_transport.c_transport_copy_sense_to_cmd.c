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
struct se_cmd {int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  scsi_sense_length; int /*<<< orphan*/  se_cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCF_TRANSPORT_TASK_SENSE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char* transport_get_sense_buffer (struct se_cmd*) ; 

void transport_copy_sense_to_cmd(struct se_cmd *cmd, unsigned char *sense)
{
	unsigned char *cmd_sense_buf;
	unsigned long flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	cmd_sense_buf = transport_get_sense_buffer(cmd);
	if (!cmd_sense_buf) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return;
	}

	cmd->se_cmd_flags |= SCF_TRANSPORT_TASK_SENSE;
	memcpy(cmd_sense_buf, sense, cmd->scsi_sense_length);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);
}