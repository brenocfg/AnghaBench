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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct bd28623_priv {struct device* dev; void* mute_gpio; void* reset_gpio; TYPE_1__* supplies; } ;
struct TYPE_3__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/ * bd28623_supply_names ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct bd28623_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bd28623_priv*) ; 
 int /*<<< orphan*/  soc_codec_bd ; 
 int /*<<< orphan*/  soc_dai_bd ; 

__attribute__((used)) static int bd28623_probe(struct platform_device *pdev)
{
	struct bd28623_priv *bd;
	struct device *dev = &pdev->dev;
	int i, ret;

	bd = devm_kzalloc(&pdev->dev, sizeof(struct bd28623_priv), GFP_KERNEL);
	if (!bd)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(bd->supplies); i++)
		bd->supplies[i].supply = bd28623_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(bd->supplies),
				      bd->supplies);
	if (ret) {
		dev_err(dev, "Failed to get supplies: %d\n", ret);
		return ret;
	}

	bd->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						 GPIOD_OUT_HIGH);
	if (IS_ERR(bd->reset_gpio)) {
		dev_err(dev, "Failed to request reset_gpio: %ld\n",
			PTR_ERR(bd->reset_gpio));
		return PTR_ERR(bd->reset_gpio);
	}

	bd->mute_gpio = devm_gpiod_get_optional(dev, "mute",
						GPIOD_OUT_HIGH);
	if (IS_ERR(bd->mute_gpio)) {
		dev_err(dev, "Failed to request mute_gpio: %ld\n",
			PTR_ERR(bd->mute_gpio));
		return PTR_ERR(bd->mute_gpio);
	}

	platform_set_drvdata(pdev, bd);
	bd->dev = dev;

	return devm_snd_soc_register_component(dev, &soc_codec_bd,
					       &soc_dai_bd, 1);
}