#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * hdmi; } ;
struct omap_dss_device {int port_num; int /*<<< orphan*/  owner; void* output_type; void* type; TYPE_2__* dev; TYPE_1__ ops; } ;
struct panel_drv_data {int /*<<< orphan*/  in; struct omap_dss_device dssdev; struct gpio_desc* hpd_gpio; struct gpio_desc* ls_oe_gpio; struct gpio_desc* ct_cp_hpd_gpio; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 void* OMAP_DISPLAY_TYPE_HDMI ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct gpio_desc* devm_gpiod_get_index (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_index_optional (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (int /*<<< orphan*/ ) ; 
 int omapdss_register_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  tpd_hdmi_ops ; 
 int tpd_probe_of (struct platform_device*) ; 

__attribute__((used)) static int tpd_probe(struct platform_device *pdev)
{
	struct omap_dss_device *dssdev;
	struct panel_drv_data *ddata;
	int r;
	struct gpio_desc *gpio;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	if (pdev->dev.of_node) {
		r = tpd_probe_of(pdev);
		if (r)
			return r;
	} else {
		return -ENODEV;
	}

	gpio = devm_gpiod_get_index_optional(&pdev->dev, NULL, 0,
		GPIOD_OUT_LOW);
	if (IS_ERR(gpio)) {
		r = PTR_ERR(gpio);
		goto err_gpio;
	}

	ddata->ct_cp_hpd_gpio = gpio;

	gpio = devm_gpiod_get_index_optional(&pdev->dev, NULL, 1,
		GPIOD_OUT_LOW);
	if (IS_ERR(gpio)) {
		r = PTR_ERR(gpio);
		goto err_gpio;
	}

	ddata->ls_oe_gpio = gpio;

	gpio = devm_gpiod_get_index(&pdev->dev, NULL, 2,
		GPIOD_IN);
	if (IS_ERR(gpio)) {
		r = PTR_ERR(gpio);
		goto err_gpio;
	}

	ddata->hpd_gpio = gpio;

	dssdev = &ddata->dssdev;
	dssdev->ops.hdmi = &tpd_hdmi_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->output_type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->owner = THIS_MODULE;
	dssdev->port_num = 1;

	r = omapdss_register_output(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register output\n");
		goto err_reg;
	}

	return 0;
err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	return r;
}