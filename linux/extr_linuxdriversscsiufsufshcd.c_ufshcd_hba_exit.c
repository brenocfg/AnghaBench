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
struct TYPE_2__ {int /*<<< orphan*/  workq; } ;
struct ufs_hba {int is_powered; TYPE_1__ clk_scaling; scalar_t__ devfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_devfreq_remove (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_clkscaling_supported (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_setup_clocks (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_setup_hba_vreg (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_setup_vreg (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_suspend_clkscaling (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_variant_hba_exit (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_hba_exit(struct ufs_hba *hba)
{
	if (hba->is_powered) {
		ufshcd_variant_hba_exit(hba);
		ufshcd_setup_vreg(hba, false);
		ufshcd_suspend_clkscaling(hba);
		if (ufshcd_is_clkscaling_supported(hba)) {
			if (hba->devfreq)
				ufshcd_suspend_clkscaling(hba);
			destroy_workqueue(hba->clk_scaling.workq);
			ufshcd_devfreq_remove(hba);
		}
		ufshcd_setup_clocks(hba, false);
		ufshcd_setup_hba_vreg(hba, false);
		hba->is_powered = false;
	}
}