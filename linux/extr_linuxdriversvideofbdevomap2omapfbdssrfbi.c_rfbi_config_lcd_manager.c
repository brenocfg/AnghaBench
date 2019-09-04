#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct dss_lcd_mgr_config {int stallmode; int fifohandcheck; scalar_t__ lcden_sig_polarity; int /*<<< orphan*/  video_port_width; int /*<<< orphan*/  io_pad_mode; } ;
struct TYPE_6__ {int hsw; int hfp; int hbp; int vsw; int interlace; int /*<<< orphan*/  sync_pclk_edge; void* de_level; int /*<<< orphan*/  data_pclk_edge; void* vsync_level; void* hsync_level; scalar_t__ vbp; scalar_t__ vfp; } ;
struct TYPE_4__ {struct omap_overlay_manager* manager; } ;
struct TYPE_5__ {TYPE_3__ timings; int /*<<< orphan*/  pixel_size; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_IO_PAD_MODE_RFBI ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_FALLING_EDGE ; 
 int /*<<< orphan*/  OMAPDSS_DRIVE_SIG_RISING_EDGE ; 
 void* OMAPDSS_SIG_ACTIVE_HIGH ; 
 int /*<<< orphan*/  dss_mgr_set_lcd_config (struct omap_overlay_manager*,struct dss_lcd_mgr_config*) ; 
 int /*<<< orphan*/  dss_mgr_set_timings (struct omap_overlay_manager*,TYPE_3__*) ; 
 TYPE_2__ rfbi ; 

__attribute__((used)) static void rfbi_config_lcd_manager(struct omap_dss_device *dssdev)
{
	struct omap_overlay_manager *mgr = rfbi.output.manager;
	struct dss_lcd_mgr_config mgr_config;

	mgr_config.io_pad_mode = DSS_IO_PAD_MODE_RFBI;

	mgr_config.stallmode = true;
	/* Do we need fifohandcheck for RFBI? */
	mgr_config.fifohandcheck = false;

	mgr_config.video_port_width = rfbi.pixel_size;
	mgr_config.lcden_sig_polarity = 0;

	dss_mgr_set_lcd_config(mgr, &mgr_config);

	/*
	 * Set rfbi.timings with default values, the x_res and y_res fields
	 * are expected to be already configured by the panel driver via
	 * omapdss_rfbi_set_size()
	 */
	rfbi.timings.hsw = 1;
	rfbi.timings.hfp = 1;
	rfbi.timings.hbp = 1;
	rfbi.timings.vsw = 1;
	rfbi.timings.vfp = 0;
	rfbi.timings.vbp = 0;

	rfbi.timings.interlace = false;
	rfbi.timings.hsync_level = OMAPDSS_SIG_ACTIVE_HIGH;
	rfbi.timings.vsync_level = OMAPDSS_SIG_ACTIVE_HIGH;
	rfbi.timings.data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
	rfbi.timings.de_level = OMAPDSS_SIG_ACTIVE_HIGH;
	rfbi.timings.sync_pclk_edge = OMAPDSS_DRIVE_SIG_FALLING_EDGE;

	dss_mgr_set_timings(mgr, &rfbi.timings);
}