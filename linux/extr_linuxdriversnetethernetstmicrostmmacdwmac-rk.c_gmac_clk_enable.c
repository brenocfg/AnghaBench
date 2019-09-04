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
struct rk_priv_data {int phy_iface; int clk_enabled; int /*<<< orphan*/  clk_mac_speed; int /*<<< orphan*/  mac_clk_tx; int /*<<< orphan*/  pclk_mac; int /*<<< orphan*/  aclk_mac; int /*<<< orphan*/  clk_phy; int /*<<< orphan*/  clk_mac_refout; int /*<<< orphan*/  clk_mac_ref; int /*<<< orphan*/  mac_clk_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PHY_INTERFACE_MODE_RMII ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int gmac_clk_enable(struct rk_priv_data *bsp_priv, bool enable)
{
	int phy_iface = bsp_priv->phy_iface;

	if (enable) {
		if (!bsp_priv->clk_enabled) {
			if (phy_iface == PHY_INTERFACE_MODE_RMII) {
				if (!IS_ERR(bsp_priv->mac_clk_rx))
					clk_prepare_enable(
						bsp_priv->mac_clk_rx);

				if (!IS_ERR(bsp_priv->clk_mac_ref))
					clk_prepare_enable(
						bsp_priv->clk_mac_ref);

				if (!IS_ERR(bsp_priv->clk_mac_refout))
					clk_prepare_enable(
						bsp_priv->clk_mac_refout);
			}

			if (!IS_ERR(bsp_priv->clk_phy))
				clk_prepare_enable(bsp_priv->clk_phy);

			if (!IS_ERR(bsp_priv->aclk_mac))
				clk_prepare_enable(bsp_priv->aclk_mac);

			if (!IS_ERR(bsp_priv->pclk_mac))
				clk_prepare_enable(bsp_priv->pclk_mac);

			if (!IS_ERR(bsp_priv->mac_clk_tx))
				clk_prepare_enable(bsp_priv->mac_clk_tx);

			if (!IS_ERR(bsp_priv->clk_mac_speed))
				clk_prepare_enable(bsp_priv->clk_mac_speed);

			/**
			 * if (!IS_ERR(bsp_priv->clk_mac))
			 *	clk_prepare_enable(bsp_priv->clk_mac);
			 */
			mdelay(5);
			bsp_priv->clk_enabled = true;
		}
	} else {
		if (bsp_priv->clk_enabled) {
			if (phy_iface == PHY_INTERFACE_MODE_RMII) {
				clk_disable_unprepare(bsp_priv->mac_clk_rx);

				clk_disable_unprepare(bsp_priv->clk_mac_ref);

				clk_disable_unprepare(bsp_priv->clk_mac_refout);
			}

			clk_disable_unprepare(bsp_priv->clk_phy);

			clk_disable_unprepare(bsp_priv->aclk_mac);

			clk_disable_unprepare(bsp_priv->pclk_mac);

			clk_disable_unprepare(bsp_priv->mac_clk_tx);

			clk_disable_unprepare(bsp_priv->clk_mac_speed);
			/**
			 * if (!IS_ERR(bsp_priv->clk_mac))
			 *	clk_disable_unprepare(bsp_priv->clk_mac);
			 */
			bsp_priv->clk_enabled = false;
		}
	}

	return 0;
}