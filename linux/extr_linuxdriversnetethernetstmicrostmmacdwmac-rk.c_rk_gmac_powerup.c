#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rk_priv_data {int phy_iface; scalar_t__ integrated_phy; TYPE_2__* ops; int /*<<< orphan*/  rx_delay; int /*<<< orphan*/  tx_delay; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_to_rmii ) (struct rk_priv_data*) ;int /*<<< orphan*/  (* set_to_rgmii ) (struct rk_priv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int gmac_clk_enable (struct rk_priv_data*,int) ; 
 int phy_power_on (struct rk_priv_data*,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  rk_gmac_integrated_phy_powerup (struct rk_priv_data*) ; 
 int /*<<< orphan*/  stub1 (struct rk_priv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rk_priv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct rk_priv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct rk_priv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct rk_priv_data*) ; 

__attribute__((used)) static int rk_gmac_powerup(struct rk_priv_data *bsp_priv)
{
	int ret;
	struct device *dev = &bsp_priv->pdev->dev;

	ret = gmac_clk_enable(bsp_priv, true);
	if (ret)
		return ret;

	/*rmii or rgmii*/
	switch (bsp_priv->phy_iface) {
	case PHY_INTERFACE_MODE_RGMII:
		dev_info(dev, "init for RGMII\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, bsp_priv->tx_delay,
					    bsp_priv->rx_delay);
		break;
	case PHY_INTERFACE_MODE_RGMII_ID:
		dev_info(dev, "init for RGMII_ID\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, 0, 0);
		break;
	case PHY_INTERFACE_MODE_RGMII_RXID:
		dev_info(dev, "init for RGMII_RXID\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, bsp_priv->tx_delay, 0);
		break;
	case PHY_INTERFACE_MODE_RGMII_TXID:
		dev_info(dev, "init for RGMII_TXID\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, 0, bsp_priv->rx_delay);
		break;
	case PHY_INTERFACE_MODE_RMII:
		dev_info(dev, "init for RMII\n");
		bsp_priv->ops->set_to_rmii(bsp_priv);
		break;
	default:
		dev_err(dev, "NO interface defined!\n");
	}

	ret = phy_power_on(bsp_priv, true);
	if (ret) {
		gmac_clk_enable(bsp_priv, false);
		return ret;
	}

	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);

	if (bsp_priv->integrated_phy)
		rk_gmac_integrated_phy_powerup(bsp_priv);

	return 0;
}