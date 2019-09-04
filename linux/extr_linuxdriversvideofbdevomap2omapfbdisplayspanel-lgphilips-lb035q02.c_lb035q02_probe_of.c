#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct panel_drv_data {struct omap_dss_device* in; int /*<<< orphan*/  backlight_gpio; struct omap_dss_device* enable_gpio; } ;
struct omap_dss_device {int dummy; } ;
typedef  struct omap_dss_device gpio_desc ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct panel_drv_data* dev_get_drvdata (TYPE_1__*) ; 
 struct omap_dss_device* devm_gpiod_get (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (struct device_node*) ; 

__attribute__((used)) static int lb035q02_probe_of(struct spi_device *spi)
{
	struct device_node *node = spi->dev.of_node;
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	struct omap_dss_device *in;
	struct gpio_desc *gpio;

	gpio = devm_gpiod_get(&spi->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(gpio)) {
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		return PTR_ERR(gpio);
	}

	ddata->enable_gpio = gpio;

	ddata->backlight_gpio = -ENOENT;

	in = omapdss_of_find_source_for_first_ep(node);
	if (IS_ERR(in)) {
		dev_err(&spi->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	ddata->in = in;

	return 0;
}