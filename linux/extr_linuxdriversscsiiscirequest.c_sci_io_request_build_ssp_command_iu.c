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
typedef  int /*<<< orphan*/  u32 ;
struct ssp_cmd_iu {int /*<<< orphan*/  cdb; scalar_t__ _r_c; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  task_prio; scalar_t__ en_fburst; scalar_t__ _r_b; scalar_t__ _r_a; scalar_t__ add_cdb_len; int /*<<< orphan*/  LUN; } ;
struct TYPE_6__ {TYPE_2__* cmd; int /*<<< orphan*/  task_attr; int /*<<< orphan*/  task_prio; int /*<<< orphan*/  LUN; } ;
struct sas_task {TYPE_3__ ssp_task; } ;
struct TYPE_4__ {struct ssp_cmd_iu cmd; } ;
struct isci_request {TYPE_1__ ssp; } ;
struct TYPE_5__ {int cmd_len; int /*<<< orphan*/  cmnd; } ;

/* Variables and functions */
 struct sas_task* isci_request_access_task (struct isci_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_swab32_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sci_io_request_build_ssp_command_iu(struct isci_request *ireq)
{
	struct ssp_cmd_iu *cmd_iu;
	struct sas_task *task = isci_request_access_task(ireq);

	cmd_iu = &ireq->ssp.cmd;

	memcpy(cmd_iu->LUN, task->ssp_task.LUN, 8);
	cmd_iu->add_cdb_len = 0;
	cmd_iu->_r_a = 0;
	cmd_iu->_r_b = 0;
	cmd_iu->en_fburst = 0; /* unsupported */
	cmd_iu->task_prio = task->ssp_task.task_prio;
	cmd_iu->task_attr = task->ssp_task.task_attr;
	cmd_iu->_r_c = 0;

	sci_swab32_cpy(&cmd_iu->cdb, task->ssp_task.cmd->cmnd,
		       (task->ssp_task.cmd->cmd_len+3) / sizeof(u32));
}