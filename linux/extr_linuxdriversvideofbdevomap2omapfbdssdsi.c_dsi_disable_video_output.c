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
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {struct omap_overlay_manager* manager; } ;
struct dsi_data {scalar_t__ mode; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dsi_display_uninit_dispc (struct platform_device*,struct omap_overlay_manager*) ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct platform_device*,int,int) ; 
 int /*<<< orphan*/  dss_mgr_disable (struct omap_overlay_manager*) ; 

__attribute__((used)) static void dsi_disable_video_output(struct omap_dss_device *dssdev, int channel)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	struct omap_overlay_manager *mgr = dsi->output.manager;

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		dsi_if_enable(dsidev, false);
		dsi_vc_enable(dsidev, channel, false);

		/* MODE, 0 = command mode */
		REG_FLD_MOD(dsidev, DSI_VC_CTRL(channel), 0, 4, 4);

		dsi_vc_enable(dsidev, channel, true);
		dsi_if_enable(dsidev, true);
	}

	dss_mgr_disable(mgr);

	dsi_display_uninit_dispc(dsidev, mgr);
}