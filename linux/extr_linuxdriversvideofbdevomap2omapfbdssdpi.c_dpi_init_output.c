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
struct TYPE_2__ {int /*<<< orphan*/ * dpi; } ;
struct omap_dss_device {char* name; int /*<<< orphan*/  owner; TYPE_1__ ops; int /*<<< orphan*/  dispc_channel; int /*<<< orphan*/  output_type; int /*<<< orphan*/  id; int /*<<< orphan*/ * dev; } ;
struct dpi_data {struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DPI ; 
 int /*<<< orphan*/  OMAP_DSS_OUTPUT_DPI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dpi_get_channel (int /*<<< orphan*/ ) ; 
 struct dpi_data* dpi_get_data_from_pdev (struct platform_device*) ; 
 int /*<<< orphan*/  dpi_ops ; 
 int /*<<< orphan*/  omapdss_register_output (struct omap_dss_device*) ; 

__attribute__((used)) static void dpi_init_output(struct platform_device *pdev)
{
	struct dpi_data *dpi = dpi_get_data_from_pdev(pdev);
	struct omap_dss_device *out = &dpi->output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->output_type = OMAP_DISPLAY_TYPE_DPI;
	out->name = "dpi.0";
	out->dispc_channel = dpi_get_channel(0);
	out->ops.dpi = &dpi_ops;
	out->owner = THIS_MODULE;

	omapdss_register_output(out);
}