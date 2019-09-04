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
struct omap_dss_device {TYPE_1__* manager; int /*<<< orphan*/  port_num; } ;
struct dpi_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  vdds_dsi_reg; scalar_t__ pll; struct omap_dss_device output; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  FEAT_DPI_USES_VDDS_DSI ; 
 int dispc_runtime_get () ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 int /*<<< orphan*/  dpi_config_lcd_manager (struct dpi_data*) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int dpi_set_mode (struct dpi_data*) ; 
 int dss_dpi_select_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int dss_mgr_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  dss_pll_disable (scalar_t__) ; 
 int dss_pll_enable (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpi_display_enable(struct omap_dss_device *dssdev)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	struct omap_dss_device *out = &dpi->output;
	int r;

	mutex_lock(&dpi->lock);

	if (dss_has_feature(FEAT_DPI_USES_VDDS_DSI) && !dpi->vdds_dsi_reg) {
		DSSERR("no VDSS_DSI regulator\n");
		r = -ENODEV;
		goto err_no_reg;
	}

	if (out->manager == NULL) {
		DSSERR("failed to enable display: no output/manager\n");
		r = -ENODEV;
		goto err_no_out_mgr;
	}

	if (dss_has_feature(FEAT_DPI_USES_VDDS_DSI)) {
		r = regulator_enable(dpi->vdds_dsi_reg);
		if (r)
			goto err_reg_enable;
	}

	r = dispc_runtime_get();
	if (r)
		goto err_get_dispc;

	r = dss_dpi_select_source(out->port_num, out->manager->id);
	if (r)
		goto err_src_sel;

	if (dpi->pll) {
		r = dss_pll_enable(dpi->pll);
		if (r)
			goto err_dsi_pll_init;
	}

	r = dpi_set_mode(dpi);
	if (r)
		goto err_set_mode;

	dpi_config_lcd_manager(dpi);

	mdelay(2);

	r = dss_mgr_enable(out->manager);
	if (r)
		goto err_mgr_enable;

	mutex_unlock(&dpi->lock);

	return 0;

err_mgr_enable:
err_set_mode:
	if (dpi->pll)
		dss_pll_disable(dpi->pll);
err_dsi_pll_init:
err_src_sel:
	dispc_runtime_put();
err_get_dispc:
	if (dss_has_feature(FEAT_DPI_USES_VDDS_DSI))
		regulator_disable(dpi->vdds_dsi_reg);
err_reg_enable:
err_no_out_mgr:
err_no_reg:
	mutex_unlock(&dpi->lock);
	return r;
}