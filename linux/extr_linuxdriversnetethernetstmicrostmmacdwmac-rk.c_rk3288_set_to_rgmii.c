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
struct rk_priv_data {int /*<<< orphan*/  grf; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int DELAY_ENABLE (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RK3288 ; 
 int RK3288_GMAC_CLK_RX_DL_CFG (int) ; 
 int RK3288_GMAC_CLK_TX_DL_CFG (int) ; 
 int RK3288_GMAC_PHY_INTF_SEL_RGMII ; 
 int RK3288_GMAC_RMII_MODE_CLR ; 
 int /*<<< orphan*/  RK3288_GRF_SOC_CON1 ; 
 int /*<<< orphan*/  RK3288_GRF_SOC_CON3 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rk3288_set_to_rgmii(struct rk_priv_data *bsp_priv,
				int tx_delay, int rx_delay)
{
	struct device *dev = &bsp_priv->pdev->dev;

	if (IS_ERR(bsp_priv->grf)) {
		dev_err(dev, "Missing rockchip,grf property\n");
		return;
	}

	regmap_write(bsp_priv->grf, RK3288_GRF_SOC_CON1,
		     RK3288_GMAC_PHY_INTF_SEL_RGMII |
		     RK3288_GMAC_RMII_MODE_CLR);
	regmap_write(bsp_priv->grf, RK3288_GRF_SOC_CON3,
		     DELAY_ENABLE(RK3288, tx_delay, rx_delay) |
		     RK3288_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3288_GMAC_CLK_TX_DL_CFG(tx_delay));
}