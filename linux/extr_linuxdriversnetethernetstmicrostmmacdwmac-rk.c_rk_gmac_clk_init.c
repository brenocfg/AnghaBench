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
struct rk_priv_data {int clk_enabled; scalar_t__ phy_iface; void* clk_phy; scalar_t__ integrated_phy; void* clk_mac; scalar_t__ clock_input; void* clk_mac_speed; void* clk_mac_refout; void* clk_mac_ref; void* pclk_mac; void* aclk_mac; void* mac_clk_tx; void* mac_clk_rx; TYPE_1__* pdev; } ;
struct plat_stmmacenet_data {scalar_t__ phy_node; struct rk_priv_data* bsp_priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_set_rate (void*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* of_clk_get (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk_gmac_clk_init(struct plat_stmmacenet_data *plat)
{
	struct rk_priv_data *bsp_priv = plat->bsp_priv;
	struct device *dev = &bsp_priv->pdev->dev;
	int ret;

	bsp_priv->clk_enabled = false;

	bsp_priv->mac_clk_rx = devm_clk_get(dev, "mac_clk_rx");
	if (IS_ERR(bsp_priv->mac_clk_rx))
		dev_err(dev, "cannot get clock %s\n",
			"mac_clk_rx");

	bsp_priv->mac_clk_tx = devm_clk_get(dev, "mac_clk_tx");
	if (IS_ERR(bsp_priv->mac_clk_tx))
		dev_err(dev, "cannot get clock %s\n",
			"mac_clk_tx");

	bsp_priv->aclk_mac = devm_clk_get(dev, "aclk_mac");
	if (IS_ERR(bsp_priv->aclk_mac))
		dev_err(dev, "cannot get clock %s\n",
			"aclk_mac");

	bsp_priv->pclk_mac = devm_clk_get(dev, "pclk_mac");
	if (IS_ERR(bsp_priv->pclk_mac))
		dev_err(dev, "cannot get clock %s\n",
			"pclk_mac");

	bsp_priv->clk_mac = devm_clk_get(dev, "stmmaceth");
	if (IS_ERR(bsp_priv->clk_mac))
		dev_err(dev, "cannot get clock %s\n",
			"stmmaceth");

	if (bsp_priv->phy_iface == PHY_INTERFACE_MODE_RMII) {
		bsp_priv->clk_mac_ref = devm_clk_get(dev, "clk_mac_ref");
		if (IS_ERR(bsp_priv->clk_mac_ref))
			dev_err(dev, "cannot get clock %s\n",
				"clk_mac_ref");

		if (!bsp_priv->clock_input) {
			bsp_priv->clk_mac_refout =
				devm_clk_get(dev, "clk_mac_refout");
			if (IS_ERR(bsp_priv->clk_mac_refout))
				dev_err(dev, "cannot get clock %s\n",
					"clk_mac_refout");
		}
	}

	bsp_priv->clk_mac_speed = devm_clk_get(dev, "clk_mac_speed");
	if (IS_ERR(bsp_priv->clk_mac_speed))
		dev_err(dev, "cannot get clock %s\n", "clk_mac_speed");

	if (bsp_priv->clock_input) {
		dev_info(dev, "clock input from PHY\n");
	} else {
		if (bsp_priv->phy_iface == PHY_INTERFACE_MODE_RMII)
			clk_set_rate(bsp_priv->clk_mac, 50000000);
	}

	if (plat->phy_node && bsp_priv->integrated_phy) {
		bsp_priv->clk_phy = of_clk_get(plat->phy_node, 0);
		if (IS_ERR(bsp_priv->clk_phy)) {
			ret = PTR_ERR(bsp_priv->clk_phy);
			dev_err(dev, "Cannot get PHY clock: %d\n", ret);
			return -EINVAL;
		}
		clk_set_rate(bsp_priv->clk_phy, 50000000);
	}

	return 0;
}