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
struct ufs_qcom_host {int is_dev_ref_clk_enabled; scalar_t__ dev_ref_clk_ctrl_mmio; int /*<<< orphan*/  dev_ref_clk_en_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ufs_qcom_dev_ref_clk_ctrl(struct ufs_qcom_host *host, bool enable)
{
	if (host->dev_ref_clk_ctrl_mmio &&
	    (enable ^ host->is_dev_ref_clk_enabled)) {
		u32 temp = readl_relaxed(host->dev_ref_clk_ctrl_mmio);

		if (enable)
			temp |= host->dev_ref_clk_en_mask;
		else
			temp &= ~host->dev_ref_clk_en_mask;

		/*
		 * If we are here to disable this clock it might be immediately
		 * after entering into hibern8 in which case we need to make
		 * sure that device ref_clk is active at least 1us after the
		 * hibern8 enter.
		 */
		if (!enable)
			udelay(1);

		writel_relaxed(temp, host->dev_ref_clk_ctrl_mmio);

		/* ensure that ref_clk is enabled/disabled before we return */
		wmb();

		/*
		 * If we call hibern8 exit after this, we need to make sure that
		 * device ref_clk is stable for at least 1us before the hibern8
		 * exit command.
		 */
		if (enable)
			udelay(1);

		host->is_dev_ref_clk_enabled = enable;
	}
}