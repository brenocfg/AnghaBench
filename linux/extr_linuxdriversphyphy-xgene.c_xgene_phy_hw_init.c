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
struct xgene_phy_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_EXT_DIFF ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_LANE ; 
 int /*<<< orphan*/  SSC_DISABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct xgene_phy_ctx* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  xgene_phy_gen_avg_val (struct xgene_phy_ctx*,int) ; 
 int xgene_phy_hw_initialize (struct xgene_phy_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_phy_hw_init(struct phy *phy)
{
	struct xgene_phy_ctx *ctx = phy_get_drvdata(phy);
	int rc;
	int i;

	rc = xgene_phy_hw_initialize(ctx, CLK_EXT_DIFF, SSC_DISABLE);
	if (rc) {
		dev_err(ctx->dev, "PHY initialize failed %d\n", rc);
		return rc;
	}

	/* Setup clock properly after PHY configuration */
	if (!IS_ERR(ctx->clk)) {
		/* HW requires an toggle of the clock */
		clk_prepare_enable(ctx->clk);
		clk_disable_unprepare(ctx->clk);
		clk_prepare_enable(ctx->clk);
	}

	/* Compute average value */
	for (i = 0; i < MAX_LANE; i++)
		xgene_phy_gen_avg_val(ctx, i);

	dev_dbg(ctx->dev, "PHY initialized\n");
	return 0;
}