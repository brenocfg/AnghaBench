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
struct ufs_hba {int /*<<< orphan*/  spm_lvl; int /*<<< orphan*/  rpm_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_PM_LVL_1 ; 
 int /*<<< orphan*/  UFS_PM_LVL_3 ; 

__attribute__((used)) static void ufs_hisi_set_pm_lvl(struct ufs_hba *hba)
{
	hba->rpm_lvl = UFS_PM_LVL_1;
	hba->spm_lvl = UFS_PM_LVL_3;
}