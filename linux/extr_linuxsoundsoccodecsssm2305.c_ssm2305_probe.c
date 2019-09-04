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
struct ssm2305 {int /*<<< orphan*/  gpiod_shutdown; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ssm2305* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ssm2305*) ; 
 int /*<<< orphan*/  ssm2305_component_driver ; 

__attribute__((used)) static int ssm2305_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ssm2305 *priv;
	int err;

	/* Allocate the private data */
	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	/* Get shutdown gpio */
	priv->gpiod_shutdown = devm_gpiod_get(dev, "shutdown",
					      GPIOD_OUT_LOW);
	if (IS_ERR(priv->gpiod_shutdown)) {
		err = PTR_ERR(priv->gpiod_shutdown);
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'shutdown' gpio: %d\n",
				err);
		return err;
	}

	return devm_snd_soc_register_component(dev, &ssm2305_component_driver,
					       NULL, 0);
}