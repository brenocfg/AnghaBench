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
typedef  int /*<<< orphan*/  u32 ;
struct ufs_qcom_phy {int is_dev_ref_clk_enabled; scalar_t__ dev_ref_clk_ctrl_mmio; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_REF_CLK_EN ; 
 struct ufs_qcom_phy* get_ufs_qcom_phy (struct phy*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ufs_qcom_phy_dev_ref_clk_ctrl(struct phy *generic_phy, bool enable)
{
	struct ufs_qcom_phy *phy = get_ufs_qcom_phy(generic_phy);

	if (phy->dev_ref_clk_ctrl_mmio &&
	    (enable ^ phy->is_dev_ref_clk_enabled)) {
		u32 temp = readl_relaxed(phy->dev_ref_clk_ctrl_mmio);

		if (enable)
			temp |= UFS_REF_CLK_EN;
		else
			temp &= ~UFS_REF_CLK_EN;

		/*
		 * If we are here to disable this clock immediately after
		 * entering into hibern8, we need to make sure that device
		 * ref_clk is active atleast 1us after the hibern8 enter.
		 */
		if (!enable)
			udelay(1);

		writel_relaxed(temp, phy->dev_ref_clk_ctrl_mmio);
		/* ensure that ref_clk is enabled/disabled before we return */
		wmb();
		/*
		 * If we call hibern8 exit after this, we need to make sure that
		 * device ref_clk is stable for atleast 1us before the hibern8
		 * exit command.
		 */
		if (enable)
			udelay(1);

		phy->is_dev_ref_clk_enabled = enable;
	}
}