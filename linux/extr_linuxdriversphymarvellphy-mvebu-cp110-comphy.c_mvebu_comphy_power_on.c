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
struct phy {int dummy; } ;
struct mvebu_comphy_priv {scalar_t__ base; int /*<<< orphan*/  regmap; } ;
struct mvebu_comphy_lane {int mode; int /*<<< orphan*/  id; int /*<<< orphan*/  port; struct mvebu_comphy_priv* priv; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  MVEBU_COMPHY_PIPE_SELECTOR ; 
 int MVEBU_COMPHY_PIPE_SELECTOR_PIPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVEBU_COMPHY_SELECTOR ; 
 int MVEBU_COMPHY_SELECTOR_PHY (int /*<<< orphan*/ ) ; 
 scalar_t__ MVEBU_COMPHY_SERDES_CFG1 (int /*<<< orphan*/ ) ; 
 int MVEBU_COMPHY_SERDES_CFG1_RF_RESET ; 
#define  PHY_MODE_10GKR 130 
#define  PHY_MODE_2500SGMII 129 
#define  PHY_MODE_SGMII 128 
 int mvebu_comphy_get_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mvebu_comphy_set_mode_10gkr (struct phy*) ; 
 int mvebu_comphy_set_mode_sgmii (struct phy*,int) ; 
 struct mvebu_comphy_lane* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mvebu_comphy_power_on(struct phy *phy)
{
	struct mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	struct mvebu_comphy_priv *priv = lane->priv;
	int ret, mux;
	u32 val;

	mux = mvebu_comphy_get_mux(lane->id, lane->port, lane->mode);
	if (mux < 0)
		return -ENOTSUPP;

	regmap_read(priv->regmap, MVEBU_COMPHY_PIPE_SELECTOR, &val);
	val &= ~(0xf << MVEBU_COMPHY_PIPE_SELECTOR_PIPE(lane->id));
	regmap_write(priv->regmap, MVEBU_COMPHY_PIPE_SELECTOR, val);

	regmap_read(priv->regmap, MVEBU_COMPHY_SELECTOR, &val);
	val &= ~(0xf << MVEBU_COMPHY_SELECTOR_PHY(lane->id));
	val |= mux << MVEBU_COMPHY_SELECTOR_PHY(lane->id);
	regmap_write(priv->regmap, MVEBU_COMPHY_SELECTOR, val);

	switch (lane->mode) {
	case PHY_MODE_SGMII:
	case PHY_MODE_2500SGMII:
		ret = mvebu_comphy_set_mode_sgmii(phy, lane->mode);
		break;
	case PHY_MODE_10GKR:
		ret = mvebu_comphy_set_mode_10gkr(phy);
		break;
	default:
		return -ENOTSUPP;
	}

	/* digital reset */
	val = readl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG1_RF_RESET;
	writel(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	return ret;
}