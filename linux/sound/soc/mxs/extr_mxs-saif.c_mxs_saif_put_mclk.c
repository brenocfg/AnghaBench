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
typedef  int u32 ;
struct mxs_saif {scalar_t__ mclk_in_use; scalar_t__ base; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SAIF_CTRL_CLKGATE ; 
 int /*<<< orphan*/  BM_SAIF_CTRL_RUN ; 
 int BM_SAIF_STAT_BUSY ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MXS_CLR_ADDR ; 
 scalar_t__ MXS_SET_ADDR ; 
 scalar_t__ SAIF_CTRL ; 
 scalar_t__ SAIF_STAT ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mxs_saif** mxs_saif ; 

int mxs_saif_put_mclk(unsigned int saif_id)
{
	struct mxs_saif *saif = mxs_saif[saif_id];
	u32 stat;

	if (!saif)
		return -EINVAL;

	stat = __raw_readl(saif->base + SAIF_STAT);
	if (stat & BM_SAIF_STAT_BUSY) {
		dev_err(saif->dev, "error: busy\n");
		return -EBUSY;
	}

	clk_disable_unprepare(saif->clk);

	/* disable MCLK output */
	__raw_writel(BM_SAIF_CTRL_CLKGATE,
		saif->base + SAIF_CTRL + MXS_SET_ADDR);
	__raw_writel(BM_SAIF_CTRL_RUN,
		saif->base + SAIF_CTRL + MXS_CLR_ADDR);

	saif->mclk_in_use = 0;
	return 0;
}