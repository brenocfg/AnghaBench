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
struct TYPE_6__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {void* timings; } ;
struct omap_dss_device {TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; TYPE_2__* dev; int /*<<< orphan*/ * driver; } ;
struct panel_drv_data {int /*<<< orphan*/  in; struct omap_dss_device dssdev; void* timings; TYPE_2__* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_VENC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 scalar_t__ dev_get_platdata (TYPE_2__*) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (int /*<<< orphan*/ ) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  tvc_driver ; 
 void* tvc_pal_timings ; 
 int tvc_probe_of (struct platform_device*) ; 
 int tvc_probe_pdata (struct platform_device*) ; 

__attribute__((used)) static int tvc_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);
	ddata->dev = &pdev->dev;

	if (dev_get_platdata(&pdev->dev)) {
		r = tvc_probe_pdata(pdev);
		if (r)
			return r;
	} else if (pdev->dev.of_node) {
		r = tvc_probe_of(pdev);
		if (r)
			return r;
	} else {
		return -ENODEV;
	}

	ddata->timings = tvc_pal_timings;

	dssdev = &ddata->dssdev;
	dssdev->driver = &tvc_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = tvc_pal_timings;

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