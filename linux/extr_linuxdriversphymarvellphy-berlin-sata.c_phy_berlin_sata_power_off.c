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
typedef  int /*<<< orphan*/  u32 ;
struct phy_berlin_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct phy_berlin_desc {int /*<<< orphan*/  power_bit; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_REGISTER ; 
 scalar_t__ HOST_VSA_ADDR ; 
 scalar_t__ HOST_VSA_DATA ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct phy_berlin_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct phy_berlin_desc* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int phy_berlin_sata_power_off(struct phy *phy)
{
	struct phy_berlin_desc *desc = phy_get_drvdata(phy);
	struct phy_berlin_priv *priv = dev_get_drvdata(phy->dev.parent);
	u32 regval;

	clk_prepare_enable(priv->clk);

	spin_lock(&priv->lock);

	/* Power down PHY */
	writel(CONTROL_REGISTER, priv->base + HOST_VSA_ADDR);
	regval = readl(priv->base + HOST_VSA_DATA);
	regval |= desc->power_bit;
	writel(regval, priv->base + HOST_VSA_DATA);

	spin_unlock(&priv->lock);

	clk_disable_unprepare(priv->clk);

	return 0;
}