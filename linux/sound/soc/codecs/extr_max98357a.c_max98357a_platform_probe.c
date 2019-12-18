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
struct max98357a_priv {scalar_t__ sdmode_delay; int /*<<< orphan*/  sdmode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct max98357a_priv*) ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct max98357a_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  max98357a_component_driver ; 
 int /*<<< orphan*/  max98357a_dai_driver ; 

__attribute__((used)) static int max98357a_platform_probe(struct platform_device *pdev)
{
	struct max98357a_priv *max98357a;
	int ret;

	max98357a = devm_kzalloc(&pdev->dev, sizeof(*max98357a), GFP_KERNEL);
	if (!max98357a)
		return -ENOMEM;

	max98357a->sdmode = devm_gpiod_get_optional(&pdev->dev,
				"sdmode", GPIOD_OUT_LOW);
	if (IS_ERR(max98357a->sdmode))
		return PTR_ERR(max98357a->sdmode);

	ret = device_property_read_u32(&pdev->dev, "sdmode-delay",
					&max98357a->sdmode_delay);
	if (ret) {
		max98357a->sdmode_delay = 0;
		dev_dbg(&pdev->dev,
			"no optional property 'sdmode-delay' found, "
			"default: no delay\n");
	}

	dev_set_drvdata(&pdev->dev, max98357a);

	return devm_snd_soc_register_component(&pdev->dev,
			&max98357a_component_driver,
			&max98357a_dai_driver, 1);
}