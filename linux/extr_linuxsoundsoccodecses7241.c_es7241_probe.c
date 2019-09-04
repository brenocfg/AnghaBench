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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct es7241_data {void* m1; void* m0; void* reset; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct es7241_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  es7241_component_driver ; 
 int /*<<< orphan*/  es7241_dai ; 
 int /*<<< orphan*/  es7241_parse_fmt (struct device*,struct es7241_data*) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct es7241_data*) ; 

__attribute__((used)) static int es7241_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct es7241_data *priv;
	int err;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	platform_set_drvdata(pdev, priv);

	priv->chip = of_device_get_match_data(dev);
	if (!priv->chip) {
		dev_err(dev, "failed to match device\n");
		return -ENODEV;
	}

	es7241_parse_fmt(dev, priv);

	priv->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(priv->reset)) {
		err = PTR_ERR(priv->reset);
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'reset' gpio: %d", err);
		return err;
	}

	priv->m0 = devm_gpiod_get_optional(dev, "m0", GPIOD_OUT_LOW);
	if (IS_ERR(priv->m0)) {
		err = PTR_ERR(priv->m0);
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'm0' gpio: %d", err);
		return err;
	}

	priv->m1 = devm_gpiod_get_optional(dev, "m1", GPIOD_OUT_LOW);
	if (IS_ERR(priv->m1)) {
		err = PTR_ERR(priv->m1);
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'm1' gpio: %d", err);
		return err;
	}

	return devm_snd_soc_register_component(&pdev->dev,
				      &es7241_component_driver,
				      &es7241_dai, 1);
}