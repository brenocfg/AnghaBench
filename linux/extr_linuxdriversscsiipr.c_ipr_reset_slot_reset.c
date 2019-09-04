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
struct ipr_ioa_cfg {int /*<<< orphan*/  reset_work_q; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; int /*<<< orphan*/  work; struct ipr_ioa_cfg* ioa_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  ipr_reset_reset_work ; 
 int /*<<< orphan*/  ipr_reset_slot_reset_done ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipr_reset_slot_reset(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	INIT_WORK(&ipr_cmd->work, ipr_reset_reset_work);
	queue_work(ioa_cfg->reset_work_q, &ipr_cmd->work);
	ipr_cmd->job_step = ipr_reset_slot_reset_done;
	LEAVE;
	return IPR_RC_JOB_RETURN;
}