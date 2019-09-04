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
struct TYPE_2__ {int is_busy_started; int /*<<< orphan*/  busy_start_t; scalar_t__ tot_busy_t; scalar_t__ window_start_t; int /*<<< orphan*/  resume_work; int /*<<< orphan*/  workq; int /*<<< orphan*/  is_allowed; int /*<<< orphan*/  active_reqs; } ;
struct ufs_hba {TYPE_1__ clk_scaling; scalar_t__ pm_op_in_progress; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_clk_scaling_start_busy(struct ufs_hba *hba)
{
	bool queue_resume_work = false;

	if (!ufshcd_is_clkscaling_supported(hba))
		return;

	if (!hba->clk_scaling.active_reqs++)
		queue_resume_work = true;

	if (!hba->clk_scaling.is_allowed || hba->pm_op_in_progress)
		return;

	if (queue_resume_work)
		queue_work(hba->clk_scaling.workq,
			   &hba->clk_scaling.resume_work);

	if (!hba->clk_scaling.window_start_t) {
		hba->clk_scaling.window_start_t = jiffies;
		hba->clk_scaling.tot_busy_t = 0;
		hba->clk_scaling.is_busy_started = false;
	}

	if (!hba->clk_scaling.is_busy_started) {
		hba->clk_scaling.busy_start_t = ktime_get();
		hba->clk_scaling.is_busy_started = true;
	}
}