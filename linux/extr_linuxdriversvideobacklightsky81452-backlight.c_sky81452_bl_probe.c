#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct sky81452_bl_platform_data {char* name; TYPE_1__ dev; int /*<<< orphan*/  gpio_enable; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; } ;
struct backlight_device {char* name; TYPE_1__ dev; int /*<<< orphan*/  gpio_enable; } ;
typedef  int /*<<< orphan*/  props ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 scalar_t__ IS_ERR (struct sky81452_bl_platform_data*) ; 
 int PTR_ERR (struct sky81452_bl_platform_data*) ; 
 char* SKY81452_DEFAULT_NAME ; 
 int /*<<< orphan*/  SKY81452_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct regmap* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct sky81452_bl_platform_data* dev_get_platdata (struct device*) ; 
 struct sky81452_bl_platform_data* devm_backlight_device_register (struct device*,char const*,struct device*,struct regmap*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sky81452_bl_platform_data*) ; 
 int /*<<< orphan*/  sky81452_bl_attr_group ; 
 int sky81452_bl_init_device (struct regmap*,struct sky81452_bl_platform_data*) ; 
 int /*<<< orphan*/  sky81452_bl_ops ; 
 struct sky81452_bl_platform_data* sky81452_bl_parse_dt (struct device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sky81452_bl_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *regmap = dev_get_drvdata(dev->parent);
	struct sky81452_bl_platform_data *pdata = dev_get_platdata(dev);
	struct backlight_device *bd;
	struct backlight_properties props;
	const char *name;
	int ret;

	if (!pdata) {
		pdata = sky81452_bl_parse_dt(dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}

	if (gpio_is_valid(pdata->gpio_enable)) {
		ret = devm_gpio_request_one(dev, pdata->gpio_enable,
					GPIOF_OUT_INIT_HIGH, "sky81452-en");
		if (ret < 0) {
			dev_err(dev, "failed to request GPIO. err=%d\n", ret);
			return ret;
		}
	}

	ret = sky81452_bl_init_device(regmap, pdata);
	if (ret < 0) {
		dev_err(dev, "failed to initialize. err=%d\n", ret);
		return ret;
	}

	memset(&props, 0, sizeof(props));
	props.max_brightness = SKY81452_MAX_BRIGHTNESS,
	name = pdata->name ? pdata->name : SKY81452_DEFAULT_NAME;
	bd = devm_backlight_device_register(dev, name, dev, regmap,
						&sky81452_bl_ops, &props);
	if (IS_ERR(bd)) {
		dev_err(dev, "failed to register. err=%ld\n", PTR_ERR(bd));
		return PTR_ERR(bd);
	}

	platform_set_drvdata(pdev, bd);

	ret = sysfs_create_group(&bd->dev.kobj, &sky81452_bl_attr_group);
	if (ret < 0) {
		dev_err(dev, "failed to create attribute. err=%d\n", ret);
		return ret;
	}

	return ret;
}