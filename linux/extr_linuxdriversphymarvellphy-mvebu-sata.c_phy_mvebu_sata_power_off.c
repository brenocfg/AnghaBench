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
struct priv {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int CTRL_PHY_SHUTDOWN ; 
 int MODE_2_FORCE_PU_RX ; 
 int MODE_2_FORCE_PU_TX ; 
 int MODE_2_PU_IVREF ; 
 int MODE_2_PU_PLL ; 
 scalar_t__ SATA_IF_CTRL ; 
 scalar_t__ SATA_PHY_MODE_2 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct priv* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int phy_mvebu_sata_power_off(struct phy *phy)
{
	struct priv *priv = phy_get_drvdata(phy);
	u32 reg;

	clk_prepare_enable(priv->clk);

	/* Disable PLL and IVREF */
	reg = readl(priv->base + SATA_PHY_MODE_2);
	reg &= ~(MODE_2_FORCE_PU_TX | MODE_2_FORCE_PU_RX |
		 MODE_2_PU_PLL | MODE_2_PU_IVREF);
	writel(reg, priv->base + SATA_PHY_MODE_2);

	/* Disable PHY */
	reg = readl(priv->base + SATA_IF_CTRL);
	reg |= CTRL_PHY_SHUTDOWN;
	writel(reg, priv->base + SATA_IF_CTRL);

	clk_disable_unprepare(priv->clk);

	return 0;
}