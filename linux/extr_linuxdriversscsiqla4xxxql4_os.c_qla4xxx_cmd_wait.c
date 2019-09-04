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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int nx_reset_timeout; TYPE_1__* host; int /*<<< orphan*/  hardware_lock; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_2__ {scalar_t__ can_queue; } ;

/* Variables and functions */
 scalar_t__ CMD_SP (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ WAIT_CMD_TOV ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,scalar_t__) ; 
 struct scsi_cmnd* scsi_host_find_tag (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after_eq (scalar_t__,unsigned long) ; 

__attribute__((used)) static int qla4xxx_cmd_wait(struct scsi_qla_host *ha)
{
	uint32_t index = 0;
	unsigned long flags;
	struct scsi_cmnd *cmd;
	unsigned long wtime;
	uint32_t wtmo;

	if (is_qla40XX(ha))
		wtmo = WAIT_CMD_TOV;
	else
		wtmo = ha->nx_reset_timeout / 2;

	wtime = jiffies + (wtmo * HZ);

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "Wait up to %u seconds for cmds to complete\n",
			  wtmo));

	while (!time_after_eq(jiffies, wtime)) {
		spin_lock_irqsave(&ha->hardware_lock, flags);
		/* Find a command that hasn't completed. */
		for (index = 0; index < ha->host->can_queue; index++) {
			cmd = scsi_host_find_tag(ha->host, index);
			/*
			 * We cannot just check if the index is valid,
			 * becase if we are run from the scsi eh, then
			 * the scsi/block layer is going to prevent
			 * the tag from being released.
			 */
			if (cmd != NULL && CMD_SP(cmd))
				break;
		}
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		/* If No Commands are pending, wait is complete */
		if (index == ha->host->can_queue)
			return QLA_SUCCESS;

		msleep(1000);
	}
	/* If we timed out on waiting for commands to come back
	 * return ERROR. */
	return QLA_ERROR;
}