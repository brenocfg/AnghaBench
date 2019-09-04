#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct panel_drv_data {struct omap_dss_device dssdev; int /*<<< orphan*/  invert_polarity; struct omap_dss_device* in; } ;
struct connector_atv_platform_data {int /*<<< orphan*/  name; int /*<<< orphan*/  invert_polarity; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct connector_atv_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct omap_dss_device* omap_dss_find_output (int /*<<< orphan*/ ) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tvc_probe_pdata(struct platform_device *pdev)
{
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct connector_atv_platform_data *pdata;
	struct omap_dss_device *in, *dssdev;

	pdata = dev_get_platdata(&pdev->dev);

	in = omap_dss_find_output(pdata->source);
	if (in == NULL) {
		dev_err(&pdev->dev, "Failed to find video source\n");
		return -EPROBE_DEFER;
	}

	ddata->in = in;

	ddata->invert_polarity = pdata->invert_polarity;

	dssdev = &ddata->dssdev;
	dssdev->name = pdata->name;

	return 0;
}