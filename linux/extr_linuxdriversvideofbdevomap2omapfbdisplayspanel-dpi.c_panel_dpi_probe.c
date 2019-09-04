#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_lines; } ;
struct TYPE_10__ {TYPE_2__ dpi; } ;
struct TYPE_8__ {int /*<<< orphan*/  timings; } ;
struct omap_dss_device {TYPE_3__ phy; TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * driver; TYPE_4__* dev; } ;
struct panel_drv_data {int /*<<< orphan*/  in; int /*<<< orphan*/  data_lines; int /*<<< orphan*/  videomode; struct omap_dss_device dssdev; int /*<<< orphan*/  backlight_gpio; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DPI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 scalar_t__ dev_get_platdata (TYPE_4__*) ; 
 int devm_gpio_request_one (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (int /*<<< orphan*/ ) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  panel_dpi_ops ; 
 int panel_dpi_probe_of (struct platform_device*) ; 
 int panel_dpi_probe_pdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int panel_dpi_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (ddata == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	if (dev_get_platdata(&pdev->dev)) {
		r = panel_dpi_probe_pdata(pdev);
		if (r)
			return r;
	} else if (pdev->dev.of_node) {
		r = panel_dpi_probe_of(pdev);
		if (r)
			return r;
	} else {
		return -ENODEV;
	}

	if (gpio_is_valid(ddata->backlight_gpio)) {
		r = devm_gpio_request_one(&pdev->dev, ddata->backlight_gpio,
				GPIOF_OUT_INIT_LOW, "panel backlight");
		if (r)
			goto err_gpio;
	}

	dssdev = &ddata->dssdev;
	dssdev->dev = &pdev->dev;
	dssdev->driver = &panel_dpi_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;
	dssdev->phy.dpi.data_lines = ddata->data_lines;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register panel\n");
		goto err_reg;
	}

	return 0;

err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	return r;
}