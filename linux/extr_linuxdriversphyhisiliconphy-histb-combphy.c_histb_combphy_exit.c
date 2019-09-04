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
struct phy {int dummy; } ;
struct histb_combphy_priv {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  por_rst; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ COMBPHY_CFG_REG ; 
 int /*<<< orphan*/  COMBPHY_CLKREF_OUT_OEN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct histb_combphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int histb_combphy_exit(struct phy *phy)
{
	struct histb_combphy_priv *priv = phy_get_drvdata(phy);
	u32 val;

	/* Disable EP clock */
	val = readl(priv->mmio + COMBPHY_CFG_REG);
	val &= ~COMBPHY_CLKREF_OUT_OEN;
	writel(val, priv->mmio + COMBPHY_CFG_REG);

	reset_control_assert(priv->por_rst);
	clk_disable_unprepare(priv->ref_clk);

	return 0;
}