#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct se_device {TYPE_2__* transport; TYPE_1__* se_hba; } ;
struct se_cmd {int se_cmd_flags; unsigned char* sense_buffer; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  scsi_sense_length; int /*<<< orphan*/  se_lun; struct se_device* se_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  hba_id; } ;

/* Variables and functions */
 int SCF_SENT_CHECK_CONDITION ; 
 int /*<<< orphan*/  TRANSPORT_SENSE_BUFFER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *transport_get_sense_buffer(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;

	WARN_ON(!cmd->se_lun);

	if (!dev)
		return NULL;

	if (cmd->se_cmd_flags & SCF_SENT_CHECK_CONDITION)
		return NULL;

	cmd->scsi_sense_length = TRANSPORT_SENSE_BUFFER;

	pr_debug("HBA_[%u]_PLUG[%s]: Requesting sense for SAM STATUS: 0x%02x\n",
		dev->se_hba->hba_id, dev->transport->name, cmd->scsi_status);
	return cmd->sense_buffer;
}