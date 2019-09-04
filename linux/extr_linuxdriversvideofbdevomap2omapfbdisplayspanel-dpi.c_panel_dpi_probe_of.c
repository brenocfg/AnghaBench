#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videomode {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct panel_drv_data {struct omap_dss_device* in; int /*<<< orphan*/  videomode; int /*<<< orphan*/  backlight_gpio; struct omap_dss_device* enable_gpio; } ;
struct omap_dss_device {int dummy; } ;
typedef  struct omap_dss_device gpio_desc ;
struct display_timing {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct omap_dss_device* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int of_get_display_timing (struct device_node*,char*,struct display_timing*) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (struct device_node*) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  videomode_from_timing (struct display_timing*,struct videomode*) ; 
 int /*<<< orphan*/  videomode_to_omap_video_timings (struct videomode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_dpi_probe_of(struct platform_device *pdev)
{
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct device_node *node = pdev->dev.of_node;
	struct omap_dss_device *in;
	int r;
	struct display_timing timing;
	struct videomode vm;
	struct gpio_desc *gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->enable_gpio = gpio;

	ddata->backlight_gpio = -ENOENT;

	r = of_get_display_timing(node, "panel-timing", &timing);
	if (r) {
		dev_err(&pdev->dev, "failed to get video timing\n");
		return r;
	}

	videomode_from_timing(&timing, &vm);
	videomode_to_omap_video_timings(&vm, &ddata->videomode);

	in = omapdss_of_find_source_for_first_ep(node);
	if (IS_ERR(in)) {
		dev_err(&pdev->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	ddata->in = in;

	return 0;
}