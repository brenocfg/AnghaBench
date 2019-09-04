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
struct ufs_clk_scaling {int is_busy_started; scalar_t__ busy_start_t; int /*<<< orphan*/  tot_busy_t; } ;
struct ufs_hba {int /*<<< orphan*/  outstanding_reqs; struct ufs_clk_scaling clk_scaling; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_clk_scaling_update_busy(struct ufs_hba *hba)
{
	struct ufs_clk_scaling *scaling = &hba->clk_scaling;

	if (!ufshcd_is_clkscaling_supported(hba))
		return;

	if (!hba->outstanding_reqs && scaling->is_busy_started) {
		scaling->tot_busy_t += ktime_to_us(ktime_sub(ktime_get(),
					scaling->busy_start_t));
		scaling->busy_start_t = 0;
		scaling->is_busy_started = false;
	}
}