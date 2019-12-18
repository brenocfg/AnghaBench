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
struct snd_soc_dai_link {TYPE_1__* cpus; } ;
struct snd_soc_card {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 struct snd_soc_card atmel_asoc_wm8904_card ; 
 struct snd_soc_dai_link atmel_asoc_wm8904_dailink ; 
 int atmel_asoc_wm8904_dt_init (struct platform_device*) ; 
 int /*<<< orphan*/  atmel_ssc_put_audio (int) ; 
 int atmel_ssc_set_audio (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int atmel_asoc_wm8904_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &atmel_asoc_wm8904_card;
	struct snd_soc_dai_link *dailink = &atmel_asoc_wm8904_dailink;
	int id, ret;

	card->dev = &pdev->dev;
	ret = atmel_asoc_wm8904_dt_init(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to init dt info\n");
		return ret;
	}

	id = of_alias_get_id((struct device_node *)dailink->cpus->of_node, "ssc");
	ret = atmel_ssc_set_audio(id);
	if (ret != 0) {
		dev_err(&pdev->dev, "failed to set SSC %d for audio\n", id);
		return ret;
	}

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed\n");
		goto err_set_audio;
	}

	return 0;

err_set_audio:
	atmel_ssc_put_audio(id);
	return ret;
}