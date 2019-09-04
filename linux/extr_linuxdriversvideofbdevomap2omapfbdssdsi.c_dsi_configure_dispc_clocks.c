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
struct platform_device {int dummy; } ;
struct dispc_clock_info {int /*<<< orphan*/  pck_div; int /*<<< orphan*/  lck_div; } ;
struct TYPE_4__ {struct dispc_clock_info clock_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  pck_div; int /*<<< orphan*/  lck_div; } ;
struct dsi_data {TYPE_2__ mgr_config; TYPE_1__ user_dispc_cinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int dispc_calc_clock_rates (unsigned long,struct dispc_clock_info*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 unsigned long dsi_get_pll_hsdiv_dispc_rate (struct platform_device*) ; 

__attribute__((used)) static int dsi_configure_dispc_clocks(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	struct dispc_clock_info dispc_cinfo;
	int r;
	unsigned long fck;

	fck = dsi_get_pll_hsdiv_dispc_rate(dsidev);

	dispc_cinfo.lck_div = dsi->user_dispc_cinfo.lck_div;
	dispc_cinfo.pck_div = dsi->user_dispc_cinfo.pck_div;

	r = dispc_calc_clock_rates(fck, &dispc_cinfo);
	if (r) {
		DSSERR("Failed to calc dispc clocks\n");
		return r;
	}

	dsi->mgr_config.clock_info = dispc_cinfo;

	return 0;
}