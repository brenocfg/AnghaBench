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
struct videomode {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_dss_device {int /*<<< orphan*/  name; } ;
struct panel_drv_data {struct omap_dss_device* in; int /*<<< orphan*/  backlight_gpio; int /*<<< orphan*/  enable_gpio; struct omap_dss_device dssdev; int /*<<< orphan*/  videomode; int /*<<< orphan*/  data_lines; } ;
struct panel_dpi_platform_data {int /*<<< orphan*/  backlight_gpio; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  name; int /*<<< orphan*/  display_timing; int /*<<< orphan*/  data_lines; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct panel_dpi_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_desc (int /*<<< orphan*/ ) ; 
 struct omap_dss_device* omap_dss_find_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  videomode_from_timing (int /*<<< orphan*/ ,struct videomode*) ; 
 int /*<<< orphan*/  videomode_to_omap_video_timings (struct videomode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_dpi_probe_pdata(struct platform_device *pdev)
{
	const struct panel_dpi_platform_data *pdata;
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct omap_dss_device *dssdev, *in;
	struct videomode vm;
	int r;

	pdata = dev_get_platdata(&pdev->dev);

	in = omap_dss_find_output(pdata->source);
	if (in == NULL) {
		dev_err(&pdev->dev, "failed to find video source '%s'\n",
				pdata->source);
		return -EPROBE_DEFER;
	}

	ddata->in = in;

	ddata->data_lines = pdata->data_lines;

	videomode_from_timing(pdata->display_timing, &vm);
	videomode_to_omap_video_timings(&vm, &ddata->videomode);

	dssdev = &ddata->dssdev;
	dssdev->name = pdata->name;

	r = devm_gpio_request_one(&pdev->dev, pdata->enable_gpio,
					GPIOF_OUT_INIT_LOW, "panel enable");
	if (r)
		goto err_gpio;

	ddata->enable_gpio = gpio_to_desc(pdata->enable_gpio);

	ddata->backlight_gpio = pdata->backlight_gpio;

	return 0;

err_gpio:
	omap_dss_put_device(ddata->in);
	return r;
}