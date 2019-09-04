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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct gpio_backlight {int /*<<< orphan*/  gpiod; int /*<<< orphan*/  def_value; } ;
struct device_node {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int gpio_backlight_probe_dt(struct platform_device *pdev,
				   struct gpio_backlight *gbl)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	enum gpiod_flags flags;
	int ret;

	gbl->def_value = of_property_read_bool(np, "default-on");
	flags = gbl->def_value ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;

	gbl->gpiod = devm_gpiod_get(dev, NULL, flags);
	if (IS_ERR(gbl->gpiod)) {
		ret = PTR_ERR(gbl->gpiod);

		if (ret != -EPROBE_DEFER) {
			dev_err(dev,
				"Error: The gpios parameter is missing or invalid.\n");
		}
		return ret;
	}

	return 0;
}