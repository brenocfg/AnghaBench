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
struct platform_device {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ ddr_clk_always_on; } ;
struct dsi_data {TYPE_1__ vm_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int) ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_force_tx_stop_mode_io (struct platform_device*) ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct platform_device*,int,int) ; 
 int /*<<< orphan*/  dsi_vc_send_null (struct omap_dss_device*,int) ; 

__attribute__((used)) static void dsi_vc_enable_hs(struct omap_dss_device *dssdev, int channel,
		bool enable)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	DSSDBG("dsi_vc_enable_hs(%d, %d)\n", channel, enable);

	WARN_ON(!dsi_bus_is_locked(dsidev));

	dsi_vc_enable(dsidev, channel, 0);
	dsi_if_enable(dsidev, 0);

	REG_FLD_MOD(dsidev, DSI_VC_CTRL(channel), enable, 9, 9);

	dsi_vc_enable(dsidev, channel, 1);
	dsi_if_enable(dsidev, 1);

	dsi_force_tx_stop_mode_io(dsidev);

	/* start the DDR clock by sending a NULL packet */
	if (dsi->vm_timings.ddr_clk_always_on && enable)
		dsi_vc_send_null(dssdev, channel);
}