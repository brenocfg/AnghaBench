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
struct TYPE_4__ {int /*<<< orphan*/  sense_interrupt_reg; } ;
struct ipr_ioa_cfg {scalar_t__ sdt_state; int /*<<< orphan*/  work_q; scalar_t__ sis64; scalar_t__ dump_timeout; TYPE_2__* pdev; TYPE_1__ regs; } ;
struct TYPE_6__ {scalar_t__ time_left; } ;
struct ipr_cmnd {TYPE_3__ u; int /*<<< orphan*/  job_step; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 scalar_t__ GET_DUMP ; 
 scalar_t__ IPR_CHECK_FOR_RESET_TIMEOUT ; 
 int IPR_PCII_MAILBOX_STABLE ; 
 int IPR_RC_JOB_RETURN ; 
 scalar_t__ IPR_SIS32_DUMP_TIMEOUT ; 
 scalar_t__ IPR_SIS64_DUMP_TIMEOUT ; 
 int /*<<< orphan*/  LEAVE ; 
 scalar_t__ READ_DUMP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ipr_reset_start_timer (struct ipr_cmnd*,scalar_t__) ; 
 int /*<<< orphan*/  ipr_reset_wait_for_dump ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipr_dump_mailbox_wait(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;

	if (ioa_cfg->sdt_state != GET_DUMP)
		return IPR_RC_JOB_RETURN;

	if (!ioa_cfg->sis64 || !ipr_cmd->u.time_left ||
	    (readl(ioa_cfg->regs.sense_interrupt_reg) &
	     IPR_PCII_MAILBOX_STABLE)) {

		if (!ipr_cmd->u.time_left)
			dev_err(&ioa_cfg->pdev->dev,
				"Timed out waiting for Mailbox register.\n");

		ioa_cfg->sdt_state = READ_DUMP;
		ioa_cfg->dump_timeout = 0;
		if (ioa_cfg->sis64)
			ipr_reset_start_timer(ipr_cmd, IPR_SIS64_DUMP_TIMEOUT);
		else
			ipr_reset_start_timer(ipr_cmd, IPR_SIS32_DUMP_TIMEOUT);
		ipr_cmd->job_step = ipr_reset_wait_for_dump;
		schedule_work(&ioa_cfg->work_q);

	} else {
		ipr_cmd->u.time_left -= IPR_CHECK_FOR_RESET_TIMEOUT;
		ipr_reset_start_timer(ipr_cmd,
				      IPR_CHECK_FOR_RESET_TIMEOUT);
	}

	LEAVE;
	return IPR_RC_JOB_RETURN;
}