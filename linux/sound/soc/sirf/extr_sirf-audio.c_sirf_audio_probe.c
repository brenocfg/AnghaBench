#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_5__* dev; } ;
struct sirf_audio_card {void* gpio_hp_pa; void* gpio_spk_pa; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_12__ {TYPE_3__* codecs; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_11__ {void* of_node; } ;
struct TYPE_10__ {void* of_node; } ;
struct TYPE_9__ {void* of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,int,...) ; 
 int devm_gpio_request_one (TYPE_5__*,void*,int /*<<< orphan*/ ,char*) ; 
 struct sirf_audio_card* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_5__*,struct snd_soc_card*) ; 
 scalar_t__ gpio_is_valid (void*) ; 
 void* of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* sirf_audio_dai_link ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct sirf_audio_card*) ; 
 struct snd_soc_card snd_soc_sirf_audio_card ; 

__attribute__((used)) static int sirf_audio_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_sirf_audio_card;
	struct sirf_audio_card *sirf_audio_card;
	int ret;

	sirf_audio_card = devm_kzalloc(&pdev->dev, sizeof(struct sirf_audio_card),
			GFP_KERNEL);
	if (sirf_audio_card == NULL)
		return -ENOMEM;

	sirf_audio_dai_link[0].cpus->of_node =
		of_parse_phandle(pdev->dev.of_node, "sirf,audio-platform", 0);
	sirf_audio_dai_link[0].platforms->of_node =
		of_parse_phandle(pdev->dev.of_node, "sirf,audio-platform", 0);
	sirf_audio_dai_link[0].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node, "sirf,audio-codec", 0);
	sirf_audio_card->gpio_spk_pa = of_get_named_gpio(pdev->dev.of_node,
			"spk-pa-gpios", 0);
	sirf_audio_card->gpio_hp_pa =  of_get_named_gpio(pdev->dev.of_node,
			"hp-pa-gpios", 0);
	if (gpio_is_valid(sirf_audio_card->gpio_spk_pa)) {
		ret = devm_gpio_request_one(&pdev->dev,
				sirf_audio_card->gpio_spk_pa,
				GPIOF_OUT_INIT_LOW, "SPA_PA_SD");
		if (ret) {
			dev_err(&pdev->dev,
				"Failed to request GPIO_%d for reset: %d\n",
				sirf_audio_card->gpio_spk_pa, ret);
			return ret;
		}
	}
	if (gpio_is_valid(sirf_audio_card->gpio_hp_pa)) {
		ret = devm_gpio_request_one(&pdev->dev,
				sirf_audio_card->gpio_hp_pa,
				GPIOF_OUT_INIT_LOW, "HP_PA_SD");
		if (ret) {
			dev_err(&pdev->dev,
				"Failed to request GPIO_%d for reset: %d\n",
				sirf_audio_card->gpio_hp_pa, ret);
			return ret;
		}
	}

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, sirf_audio_card);

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed:%d\n", ret);

	return ret;
}