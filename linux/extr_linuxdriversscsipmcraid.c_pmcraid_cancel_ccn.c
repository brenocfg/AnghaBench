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
struct pmcraid_cmd {TYPE_3__* ioa_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cdb; } ;
struct TYPE_6__ {TYPE_2__ ioasa; TYPE_1__ ioarcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_HCAM_CODE_CONFIG_CHANGE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_cancel_hcam (struct pmcraid_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_ioa_shutdown ; 
 int /*<<< orphan*/  pmcraid_reinit_cmdblk (struct pmcraid_cmd*) ; 

__attribute__((used)) static void pmcraid_cancel_ccn(struct pmcraid_cmd *cmd)
{
	pmcraid_info("response for Cancel LDN CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	pmcraid_reinit_cmdblk(cmd);

	pmcraid_cancel_hcam(cmd,
			    PMCRAID_HCAM_CODE_CONFIG_CHANGE,
			    pmcraid_ioa_shutdown);
}