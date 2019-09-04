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
struct omap_video_timings {unsigned long pixelclock; } ;
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_4__ {struct omap_overlay_manager* manager; } ;
struct dpi_data {scalar_t__ pll; TYPE_1__ output; } ;
struct TYPE_6__ {int lck_div; int pck_div; } ;
struct TYPE_5__ {unsigned long* clkout; } ;
struct dpi_clk_calc_ctx {unsigned long fck; TYPE_3__ dispc_cinfo; TYPE_2__ dsi_cinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HSDIV_DISPC ; 
 int /*<<< orphan*/  dispc_mgr_timings_ok (int /*<<< orphan*/ ,struct omap_video_timings*) ; 
 int dpi_dsi_clk_calc (struct dpi_data*,unsigned long,struct dpi_clk_calc_ctx*) ; 
 int dpi_dss_clk_calc (unsigned long,struct dpi_clk_calc_ctx*) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 

__attribute__((used)) static int dpi_check_timings(struct omap_dss_device *dssdev,
			struct omap_video_timings *timings)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	struct omap_overlay_manager *mgr = dpi->output.manager;
	int lck_div, pck_div;
	unsigned long fck;
	unsigned long pck;
	struct dpi_clk_calc_ctx ctx;
	bool ok;

	if (mgr && !dispc_mgr_timings_ok(mgr->id, timings))
		return -EINVAL;

	if (timings->pixelclock == 0)
		return -EINVAL;

	if (dpi->pll) {
		ok = dpi_dsi_clk_calc(dpi, timings->pixelclock, &ctx);
		if (!ok)
			return -EINVAL;

		fck = ctx.dsi_cinfo.clkout[HSDIV_DISPC];
	} else {
		ok = dpi_dss_clk_calc(timings->pixelclock, &ctx);
		if (!ok)
			return -EINVAL;

		fck = ctx.fck;
	}

	lck_div = ctx.dispc_cinfo.lck_div;
	pck_div = ctx.dispc_cinfo.pck_div;

	pck = fck / lck_div / pck_div;

	timings->pixelclock = pck;

	return 0;
}