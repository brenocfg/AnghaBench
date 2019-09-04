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
struct panel_drv_data {struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* dpi; } ;
struct omap_dss_device {int /*<<< orphan*/  state; TYPE_2__ ops; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable ) (struct omap_dss_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  JBT_REG_DISPLAY_OFF ; 
 int /*<<< orphan*/  JBT_REG_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  JBT_REG_POWER_ON_OFF ; 
 int /*<<< orphan*/  JBT_REG_SLEEP_IN ; 
 int /*<<< orphan*/  OMAP_DSS_DISPLAY_DISABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jbt_reg_write_1 (struct panel_drv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jbt_reg_write_2 (struct panel_drv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jbt_ret_write_0 (struct panel_drv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapdss_device_is_enabled (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void td028ttec1_panel_disable(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *in = ddata->in;

	if (!omapdss_device_is_enabled(dssdev))
		return;

	dev_dbg(dssdev->dev, "td028ttec1_panel_disable()\n");

	jbt_ret_write_0(ddata, JBT_REG_DISPLAY_OFF);
	jbt_reg_write_2(ddata, JBT_REG_OUTPUT_CONTROL, 0x8002);
	jbt_ret_write_0(ddata, JBT_REG_SLEEP_IN);
	jbt_reg_write_1(ddata, JBT_REG_POWER_ON_OFF, 0x00);

	in->ops.dpi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
}