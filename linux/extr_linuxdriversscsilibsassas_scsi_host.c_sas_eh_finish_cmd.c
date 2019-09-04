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
struct scsi_cmnd {int /*<<< orphan*/  eh_entry; TYPE_1__* device; } ;
struct sas_task {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  eh_done_q; int /*<<< orphan*/  eh_ata_q; } ;
struct domain_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct sas_ha_struct* SHOST_TO_SAS_HA (int /*<<< orphan*/ ) ; 
 struct sas_task* TO_SAS_TASK (struct scsi_cmnd*) ; 
 struct domain_device* cmd_to_domain_dev (struct scsi_cmnd*) ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_end_task (struct scsi_cmnd*,struct sas_task*) ; 
 int /*<<< orphan*/  scsi_eh_finish_cmd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sas_eh_finish_cmd(struct scsi_cmnd *cmd)
{
	struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(cmd->device->host);
	struct domain_device *dev = cmd_to_domain_dev(cmd);
	struct sas_task *task = TO_SAS_TASK(cmd);

	/* At this point, we only get called following an actual abort
	 * of the task, so we should be guaranteed not to be racing with
	 * any completions from the LLD.  Task is freed after this.
	 */
	sas_end_task(cmd, task);

	if (dev_is_sata(dev)) {
		/* defer commands to libata so that libata EH can
		 * handle ata qcs correctly
		 */
		list_move_tail(&cmd->eh_entry, &sas_ha->eh_ata_q);
		return;
	}

	/* now finish the command and move it on to the error
	 * handler done list, this also takes it off the
	 * error handler pending list.
	 */
	scsi_eh_finish_cmd(cmd, &sas_ha->eh_done_q);
}