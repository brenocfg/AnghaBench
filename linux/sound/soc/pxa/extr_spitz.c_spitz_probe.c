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
struct snd_soc_card {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AKITA_GPIO_MIC_BIAS ; 
 int /*<<< orphan*/  SPITZ_GPIO_MIC_BIAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ machine_is_akita () ; 
 struct snd_soc_card snd_soc_spitz ; 
 int /*<<< orphan*/  spitz_mic_gpio ; 

__attribute__((used)) static int spitz_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_spitz;
	int ret;

	if (machine_is_akita())
		spitz_mic_gpio = AKITA_GPIO_MIC_BIAS;
	else
		spitz_mic_gpio = SPITZ_GPIO_MIC_BIAS;

	ret = gpio_request(spitz_mic_gpio, "MIC GPIO");
	if (ret)
		goto err1;

	ret = gpio_direction_output(spitz_mic_gpio, 0);
	if (ret)
		goto err2;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		goto err2;
	}

	return 0;

err2:
	gpio_free(spitz_mic_gpio);
err1:
	return ret;
}