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
struct ufs_hba {TYPE_1__* vops; } ;
typedef  enum ufs_notify_change_status { ____Placeholder_ufs_notify_change_status } ufs_notify_change_status ;
struct TYPE_2__ {int (* clk_scale_notify ) (struct ufs_hba*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct ufs_hba*,int,int) ; 

__attribute__((used)) static inline int ufshcd_vops_clk_scale_notify(struct ufs_hba *hba,
			bool up, enum ufs_notify_change_status status)
{
	if (hba->vops && hba->vops->clk_scale_notify)
		return hba->vops->clk_scale_notify(hba, up, status);
	return 0;
}