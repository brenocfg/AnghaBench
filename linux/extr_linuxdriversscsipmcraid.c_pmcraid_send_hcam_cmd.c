#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pmcraid_cmd {int /*<<< orphan*/  cmd_done; TYPE_5__* drv_inst; TYPE_2__* ioa_cb; } ;
struct TYPE_9__ {int /*<<< orphan*/  ignore; } ;
struct TYPE_8__ {int /*<<< orphan*/  ignore; } ;
struct TYPE_10__ {TYPE_4__ ldn; TYPE_3__ ccn; } ;
struct TYPE_6__ {scalar_t__* cdb; } ;
struct TYPE_7__ {TYPE_1__ ioarcb; } ;

/* Variables and functions */
 scalar_t__ PMCRAID_HCAM_CODE_CONFIG_CHANGE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_send_cmd (struct pmcraid_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pmcraid_send_hcam_cmd(struct pmcraid_cmd *cmd)
{
	if (cmd->ioa_cb->ioarcb.cdb[1] == PMCRAID_HCAM_CODE_CONFIG_CHANGE)
		atomic_set(&(cmd->drv_inst->ccn.ignore), 0);
	else
		atomic_set(&(cmd->drv_inst->ldn.ignore), 0);

	pmcraid_send_cmd(cmd, cmd->cmd_done, 0, NULL);
}