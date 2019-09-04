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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rockchip_usb3phy_port_cfg {int /*<<< orphan*/  typec_conn_dir; } ;
struct rockchip_typec_phy {int /*<<< orphan*/  clk_core; int /*<<< orphan*/  clk_ref; int /*<<< orphan*/  tcphy_rst; int /*<<< orphan*/  uphy_rst; int /*<<< orphan*/  pipe_rst; int /*<<< orphan*/  dev; scalar_t__ base; scalar_t__ flip; struct rockchip_usb3phy_port_cfg* port_cfgs; } ;

/* Variables and functions */
 int CMN_READY ; 
 scalar_t__ DP_MODE_CTL ; 
 int /*<<< orphan*/  DP_MODE_ENTER_A2 ; 
 int ETIMEDOUT ; 
 scalar_t__ MODE_DFP_DP ; 
 int /*<<< orphan*/  PHY_MODE_SET_TIMEOUT ; 
 int /*<<< orphan*/  PIN_ASSIGN_C_E ; 
 int /*<<< orphan*/  PIN_ASSIGN_D_F ; 
 scalar_t__ PMA_CMN_CTRL1 ; 
 scalar_t__ PMA_LANE_CFG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  property_enable (struct rockchip_typec_phy*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  readl ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcphy_cfg_24m (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  tcphy_cfg_dp_pll (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  tcphy_cfg_usb3_pll (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  tcphy_dp_aux_set_flip (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  tcphy_dp_cfg_lane (struct rockchip_typec_phy*,int) ; 
 int /*<<< orphan*/  tcphy_rx_usb3_cfg_lane (struct rockchip_typec_phy*,int) ; 
 int /*<<< orphan*/  tcphy_tx_usb3_cfg_lane (struct rockchip_typec_phy*,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tcphy_phy_init(struct rockchip_typec_phy *tcphy, u8 mode)
{
	const struct rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;
	int ret, i;
	u32 val;

	ret = clk_prepare_enable(tcphy->clk_core);
	if (ret) {
		dev_err(tcphy->dev, "Failed to prepare_enable core clock\n");
		return ret;
	}

	ret = clk_prepare_enable(tcphy->clk_ref);
	if (ret) {
		dev_err(tcphy->dev, "Failed to prepare_enable ref clock\n");
		goto err_clk_core;
	}

	reset_control_deassert(tcphy->tcphy_rst);

	property_enable(tcphy, &cfg->typec_conn_dir, tcphy->flip);
	tcphy_dp_aux_set_flip(tcphy);

	tcphy_cfg_24m(tcphy);

	if (mode == MODE_DFP_DP) {
		tcphy_cfg_dp_pll(tcphy);
		for (i = 0; i < 4; i++)
			tcphy_dp_cfg_lane(tcphy, i);

		writel(PIN_ASSIGN_C_E, tcphy->base + PMA_LANE_CFG);
	} else {
		tcphy_cfg_usb3_pll(tcphy);
		tcphy_cfg_dp_pll(tcphy);
		if (tcphy->flip) {
			tcphy_tx_usb3_cfg_lane(tcphy, 3);
			tcphy_rx_usb3_cfg_lane(tcphy, 2);
			tcphy_dp_cfg_lane(tcphy, 0);
			tcphy_dp_cfg_lane(tcphy, 1);
		} else {
			tcphy_tx_usb3_cfg_lane(tcphy, 0);
			tcphy_rx_usb3_cfg_lane(tcphy, 1);
			tcphy_dp_cfg_lane(tcphy, 2);
			tcphy_dp_cfg_lane(tcphy, 3);
		}

		writel(PIN_ASSIGN_D_F, tcphy->base + PMA_LANE_CFG);
	}

	writel(DP_MODE_ENTER_A2, tcphy->base + DP_MODE_CTL);

	reset_control_deassert(tcphy->uphy_rst);

	ret = readx_poll_timeout(readl, tcphy->base + PMA_CMN_CTRL1,
				 val, val & CMN_READY, 10,
				 PHY_MODE_SET_TIMEOUT);
	if (ret < 0) {
		dev_err(tcphy->dev, "wait pma ready timeout\n");
		ret = -ETIMEDOUT;
		goto err_wait_pma;
	}

	reset_control_deassert(tcphy->pipe_rst);

	return 0;

err_wait_pma:
	reset_control_assert(tcphy->uphy_rst);
	reset_control_assert(tcphy->tcphy_rst);
	clk_disable_unprepare(tcphy->clk_ref);
err_clk_core:
	clk_disable_unprepare(tcphy->clk_core);
	return ret;
}