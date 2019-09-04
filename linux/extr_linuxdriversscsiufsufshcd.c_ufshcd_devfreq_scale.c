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
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POST_CHANGE ; 
 int ufshcd_clock_scaling_prepare (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_clock_scaling_unprepare (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_hold (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_release (struct ufs_hba*) ; 
 int ufshcd_scale_clks (struct ufs_hba*,int) ; 
 int ufshcd_scale_gear (struct ufs_hba*,int) ; 
 int ufshcd_vops_clk_scale_notify (struct ufs_hba*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_devfreq_scale(struct ufs_hba *hba, bool scale_up)
{
	int ret = 0;

	/* let's not get into low power until clock scaling is completed */
	ufshcd_hold(hba, false);

	ret = ufshcd_clock_scaling_prepare(hba);
	if (ret)
		return ret;

	/* scale down the gear before scaling down clocks */
	if (!scale_up) {
		ret = ufshcd_scale_gear(hba, false);
		if (ret)
			goto out;
	}

	ret = ufshcd_scale_clks(hba, scale_up);
	if (ret) {
		if (!scale_up)
			ufshcd_scale_gear(hba, true);
		goto out;
	}

	/* scale up the gear after scaling up clocks */
	if (scale_up) {
		ret = ufshcd_scale_gear(hba, true);
		if (ret) {
			ufshcd_scale_clks(hba, false);
			goto out;
		}
	}

	ret = ufshcd_vops_clk_scale_notify(hba, scale_up, POST_CHANGE);

out:
	ufshcd_clock_scaling_unprepare(hba);
	ufshcd_release(hba);
	return ret;
}