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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gpio_desc* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (int /*<<< orphan*/ *,struct gpio_desc*) ; 
 int /*<<< orphan*/  snd_soc_smartq ; 

__attribute__((used)) static int smartq_probe(struct platform_device *pdev)
{
	struct gpio_desc *gpio;
	int ret;

	platform_set_drvdata(pdev, &snd_soc_smartq);

	/* Initialise GPIOs used by amplifiers */
	gpio = devm_gpiod_get(&pdev->dev, "amplifiers shutdown",
			      GPIOD_OUT_HIGH);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "Failed to register GPK12\n");
		ret = PTR_ERR(gpio);
		goto out;
	}
	snd_soc_card_set_drvdata(&snd_soc_smartq, gpio);

	ret = devm_snd_soc_register_card(&pdev->dev, &snd_soc_smartq);
	if (ret)
		dev_err(&pdev->dev, "Failed to register card\n");

out:
	return ret;
}