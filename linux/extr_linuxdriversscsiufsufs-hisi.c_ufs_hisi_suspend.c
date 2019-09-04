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
struct ufs_hisi_host {int in_suspend; } ;
struct ufs_hba {int dummy; } ;
typedef  enum ufs_pm_op { ____Placeholder_ufs_pm_op } ufs_pm_op ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SYSCTRL_REF_CLOCK_EN ; 
 int /*<<< orphan*/  PHY_CLK_CTRL ; 
 int /*<<< orphan*/  UFS_DEVICE_RESET_CTRL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  ufs_sys_ctrl_clr_bits (struct ufs_hisi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_sys_ctrl_writel (struct ufs_hisi_host*,int,int /*<<< orphan*/ ) ; 
 struct ufs_hisi_host* ufshcd_get_variant (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_runtime_pm (int) ; 

__attribute__((used)) static int ufs_hisi_suspend(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	struct ufs_hisi_host *host = ufshcd_get_variant(hba);

	if (ufshcd_is_runtime_pm(pm_op))
		return 0;

	if (host->in_suspend) {
		WARN_ON(1);
		return 0;
	}

	ufs_sys_ctrl_clr_bits(host, BIT_SYSCTRL_REF_CLOCK_EN, PHY_CLK_CTRL);
	udelay(10);
	/* set ref_dig_clk override of PHY PCS to 0 */
	ufs_sys_ctrl_writel(host, 0x00100000, UFS_DEVICE_RESET_CTRL);

	host->in_suspend = true;

	return 0;
}