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
struct ufs_vreg_info {TYPE_1__* vccq; } ;
struct ufs_hba {int /*<<< orphan*/  dev; struct ufs_vreg_info vreg_info; } ;
struct TYPE_2__ {int unused; } ;

/* Variables and functions */
 int ufshcd_toggle_vreg (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int ufshcd_set_vccq_rail_unused(struct ufs_hba *hba, bool unused)
{
	int ret = 0;
	struct ufs_vreg_info *info = &hba->vreg_info;

	if (!info)
		goto out;
	else if (!info->vccq)
		goto out;

	if (unused) {
		/* shut off the rail here */
		ret = ufshcd_toggle_vreg(hba->dev, info->vccq, false);
		/*
		 * Mark this rail as no longer used, so it doesn't get enabled
		 * later by mistake
		 */
		if (!ret)
			info->vccq->unused = true;
	} else {
		/*
		 * rail should have been already enabled hence just make sure
		 * that unused flag is cleared.
		 */
		info->vccq->unused = false;
	}
out:
	return ret;
}