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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct byt_max98090_private {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_byt_max98090_gpios ; 
 TYPE_1__ byt_max98090_card ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_acpi_dev_add_driver_gpios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct byt_max98090_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct byt_max98090_private*) ; 

__attribute__((used)) static int byt_max98090_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct byt_max98090_private *priv;
	int ret_val;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "allocation failed\n");
		return -ENOMEM;
	}

	ret_val = devm_acpi_dev_add_driver_gpios(dev->parent, acpi_byt_max98090_gpios);
	if (ret_val)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	byt_max98090_card.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&byt_max98090_card, priv);
	ret_val = devm_snd_soc_register_card(&pdev->dev, &byt_max98090_card);
	if (ret_val) {
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		return ret_val;
	}

	return 0;
}