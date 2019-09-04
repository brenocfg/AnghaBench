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
struct platform_device {int dummy; } ;
struct dsi_data {int vdds_dsi_enabled; int /*<<< orphan*/  vdds_dsi_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PLL_POWER_OFF ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_disable_scp_clk (struct platform_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_pll_power (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_pll_uninit(struct platform_device *dsidev, bool disconnect_lanes)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	dsi_pll_power(dsidev, DSI_PLL_POWER_OFF);
	if (disconnect_lanes) {
		WARN_ON(!dsi->vdds_dsi_enabled);
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	}

	dsi_disable_scp_clk(dsidev);
	dsi_runtime_put(dsidev);

	DSSDBG("PLL uninit done\n");
}