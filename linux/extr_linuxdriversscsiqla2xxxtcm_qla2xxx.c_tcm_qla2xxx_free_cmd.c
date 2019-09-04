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
struct qla_tgt_cmd {int cmd_in_wq; int trc_flags; int /*<<< orphan*/  work; TYPE_2__* qpair; } ;
struct TYPE_3__ {int /*<<< orphan*/  core_qla_free_cmd; } ;
struct TYPE_4__ {TYPE_1__ tgt_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TRC_CMD_DONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tcm_qla2xxx_complete_free ; 
 int /*<<< orphan*/  tcm_qla2xxx_free_wq ; 

__attribute__((used)) static void tcm_qla2xxx_free_cmd(struct qla_tgt_cmd *cmd)
{
	cmd->qpair->tgt_counters.core_qla_free_cmd++;
	cmd->cmd_in_wq = 1;

	WARN_ON(cmd->trc_flags & TRC_CMD_DONE);
	cmd->trc_flags |= TRC_CMD_DONE;

	INIT_WORK(&cmd->work, tcm_qla2xxx_complete_free);
	queue_work_on(smp_processor_id(), tcm_qla2xxx_free_wq, &cmd->work);
}