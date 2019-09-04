#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct megasas_instance {int max_scsi_cmds; TYPE_2__* pdev; struct fusion_context* ctrl_context; } ;
struct megasas_cmd_fusion {TYPE_3__* scmd; int /*<<< orphan*/  index; } ;
struct fusion_context {struct megasas_cmd_fusion** cmd_list; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int id; int channel; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_print_command (TYPE_3__*) ; 

__attribute__((used)) static int megasas_track_scsiio(struct megasas_instance *instance,
		int id, int channel)
{
	int i, found = 0;
	struct megasas_cmd_fusion *cmd_fusion;
	struct fusion_context *fusion;
	fusion = instance->ctrl_context;

	for (i = 0 ; i < instance->max_scsi_cmds; i++) {
		cmd_fusion = fusion->cmd_list[i];
		if (cmd_fusion->scmd &&
			(cmd_fusion->scmd->device->id == id &&
			cmd_fusion->scmd->device->channel == channel)) {
			dev_info(&instance->pdev->dev,
				"SCSI commands pending to target"
				"channel %d id %d \tSMID: 0x%x\n",
				channel, id, cmd_fusion->index);
			scsi_print_command(cmd_fusion->scmd);
			found = 1;
			break;
		}
	}

	return found ? FAILED : SUCCESS;
}