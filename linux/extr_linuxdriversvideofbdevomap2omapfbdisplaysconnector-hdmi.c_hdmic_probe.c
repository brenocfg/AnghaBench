#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {void* timings; } ;
struct omap_dss_device {TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; TYPE_2__* dev; int /*<<< orphan*/ * driver; } ;
struct panel_drv_data {int /*<<< orphan*/  in; struct omap_dss_device dssdev; void* timings; int /*<<< orphan*/  hpd_gpio; TYPE_2__* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_DIR_IN ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_HDMI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int devm_gpio_request_one (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 void* hdmic_default_timings ; 
 int /*<<< orphan*/  hdmic_driver ; 
 int hdmic_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  omap_dss_put_device (int /*<<< orphan*/ ) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int hdmic_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	if (!pdev->dev.of_node)
		return -ENODEV;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);
	ddata->dev = &pdev->dev;

	r = hdmic_probe_of(pdev);
	if (r)
		return r;

	if (gpio_is_valid(ddata->hpd_gpio)) {
		r = devm_gpio_request_one(&pdev->dev, ddata->hpd_gpio,
				GPIOF_DIR_IN, "hdmi_hpd");
		if (r)
			goto err_reg;
	}

	ddata->timings = hdmic_default_timings;

	dssdev = &ddata->dssdev;
	dssdev->driver = &hdmic_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = hdmic_default_timings;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register panel\n");
		goto err_reg;
	}

	return 0;
err_reg:
	omap_dss_put_device(ddata->in);
	return r;
}