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
struct TYPE_3__ {struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct panel_drv_data {int res_gpio; struct omap_dss_device* in; int /*<<< orphan*/  qvga_gpio; } ;
struct omap_dss_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct panel_drv_data* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (struct device_node*) ; 

__attribute__((used)) static int nec_8048_probe_of(struct spi_device *spi)
{
	struct device_node *node = spi->dev.of_node;
	struct panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	struct omap_dss_device *in;
	int gpio;

	gpio = of_get_named_gpio(node, "reset-gpios", 0);
	if (!gpio_is_valid(gpio)) {
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		return gpio;
	}
	ddata->res_gpio = gpio;

	/* XXX the panel spec doesn't mention any QVGA pin?? */
	ddata->qvga_gpio = -ENOENT;

	in = omapdss_of_find_source_for_first_ep(node);
	if (IS_ERR(in)) {
		dev_err(&spi->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	ddata->in = in;

	return 0;
}