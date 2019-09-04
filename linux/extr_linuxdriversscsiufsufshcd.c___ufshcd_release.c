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
struct TYPE_2__ {int /*<<< orphan*/  delay_ms; int /*<<< orphan*/  gate_work; int /*<<< orphan*/  clk_gating_workq; int /*<<< orphan*/  state; scalar_t__ is_suspended; scalar_t__ active_reqs; } ;
struct ufs_hba {scalar_t__ ufshcd_state; TYPE_1__ clk_gating; int /*<<< orphan*/  dev; scalar_t__ uic_async_done; scalar_t__ active_uic_cmd; scalar_t__ outstanding_tasks; scalar_t__ lrb_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_CLKS_OFF ; 
 scalar_t__ UFSHCD_STATE_OPERATIONAL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_clk_gating (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ufshcd_eh_in_progress (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_is_clkgating_allowed (struct ufs_hba*) ; 

__attribute__((used)) static void __ufshcd_release(struct ufs_hba *hba)
{
	if (!ufshcd_is_clkgating_allowed(hba))
		return;

	hba->clk_gating.active_reqs--;

	if (hba->clk_gating.active_reqs || hba->clk_gating.is_suspended
		|| hba->ufshcd_state != UFSHCD_STATE_OPERATIONAL
		|| hba->lrb_in_use || hba->outstanding_tasks
		|| hba->active_uic_cmd || hba->uic_async_done
		|| ufshcd_eh_in_progress(hba))
		return;

	hba->clk_gating.state = REQ_CLKS_OFF;
	trace_ufshcd_clk_gating(dev_name(hba->dev), hba->clk_gating.state);
	queue_delayed_work(hba->clk_gating.clk_gating_workq,
			   &hba->clk_gating.gate_work,
			   msecs_to_jiffies(hba->clk_gating.delay_ms));
}