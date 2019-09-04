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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dsi; } ;
struct omap_dss_device {char* name; int /*<<< orphan*/  owner; TYPE_1__ ops; int /*<<< orphan*/  dispc_channel; int /*<<< orphan*/  output_type; int /*<<< orphan*/  id; int /*<<< orphan*/ * dev; } ;
struct dsi_data {scalar_t__ module_id; struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DSI ; 
 int /*<<< orphan*/  OMAP_DSS_OUTPUT_DSI1 ; 
 int /*<<< orphan*/  OMAP_DSS_OUTPUT_DSI2 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dsi_get_channel (scalar_t__) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_ops ; 
 int /*<<< orphan*/  omapdss_register_output (struct omap_dss_device*) ; 

__attribute__((used)) static void dsi_init_output(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	struct omap_dss_device *out = &dsi->output;

	out->dev = &dsidev->dev;
	out->id = dsi->module_id == 0 ?
			OMAP_DSS_OUTPUT_DSI1 : OMAP_DSS_OUTPUT_DSI2;

	out->output_type = OMAP_DISPLAY_TYPE_DSI;
	out->name = dsi->module_id == 0 ? "dsi.0" : "dsi.1";
	out->dispc_channel = dsi_get_channel(dsi->module_id);
	out->ops.dsi = &dsi_ops;
	out->owner = THIS_MODULE;

	omapdss_register_output(out);
}