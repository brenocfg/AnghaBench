#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_8__* dev; } ;
struct rx51_audio_pdata {void* speaker_amp_gpio; void* eci_sw_gpio; void* jack_detection_gpio; void* tvout_selection_gpio; } ;
struct TYPE_19__ {struct device_node* of_node; } ;
struct platform_device {TYPE_8__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_15__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;
struct TYPE_18__ {TYPE_4__ dlc; } ;
struct TYPE_17__ {struct device_node* of_node; int /*<<< orphan*/ * dev_name; } ;
struct TYPE_16__ {TYPE_3__* codecs; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_14__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;
struct TYPE_13__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;
struct TYPE_12__ {struct device_node* of_node; int /*<<< orphan*/ * dai_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_ASIS ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_8__*,char*,...) ; 
 void* devm_gpiod_get (TYPE_8__*,char*,int /*<<< orphan*/ ) ; 
 struct rx51_audio_pdata* devm_kzalloc (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_8__*,struct snd_soc_card*) ; 
 int /*<<< orphan*/  machine_is_nokia_rx51 () ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 TYPE_7__* rx51_aux_dev ; 
 TYPE_6__* rx51_codec_conf ; 
 TYPE_5__* rx51_dai ; 
 struct snd_soc_card rx51_sound_card ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct rx51_audio_pdata*) ; 

__attribute__((used)) static int rx51_soc_probe(struct platform_device *pdev)
{
	struct rx51_audio_pdata *pdata;
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &rx51_sound_card;
	int err;

	if (!machine_is_nokia_rx51() && !of_machine_is_compatible("nokia,omap3-n900"))
		return -ENODEV;

	card->dev = &pdev->dev;

	if (np) {
		struct device_node *dai_node;

		dai_node = of_parse_phandle(np, "nokia,cpu-dai", 0);
		if (!dai_node) {
			dev_err(&pdev->dev, "McBSP node is not provided\n");
			return -EINVAL;
		}
		rx51_dai[0].cpus->dai_name = NULL;
		rx51_dai[0].platforms->name = NULL;
		rx51_dai[0].cpus->of_node = dai_node;
		rx51_dai[0].platforms->of_node = dai_node;

		dai_node = of_parse_phandle(np, "nokia,audio-codec", 0);
		if (!dai_node) {
			dev_err(&pdev->dev, "Codec node is not provided\n");
			return -EINVAL;
		}
		rx51_dai[0].codecs->name = NULL;
		rx51_dai[0].codecs->of_node = dai_node;

		dai_node = of_parse_phandle(np, "nokia,audio-codec", 1);
		if (!dai_node) {
			dev_err(&pdev->dev, "Auxiliary Codec node is not provided\n");
			return -EINVAL;
		}
		rx51_aux_dev[0].dlc.name = NULL;
		rx51_aux_dev[0].dlc.of_node = dai_node;
		rx51_codec_conf[0].dev_name = NULL;
		rx51_codec_conf[0].of_node = dai_node;

		dai_node = of_parse_phandle(np, "nokia,headphone-amplifier", 0);
		if (!dai_node) {
			dev_err(&pdev->dev, "Headphone amplifier node is not provided\n");
			return -EINVAL;
		}
		rx51_aux_dev[1].dlc.name = NULL;
		rx51_aux_dev[1].dlc.of_node = dai_node;
		rx51_codec_conf[1].dev_name = NULL;
		rx51_codec_conf[1].of_node = dai_node;
	}

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (pdata == NULL)
		return -ENOMEM;

	snd_soc_card_set_drvdata(card, pdata);

	pdata->tvout_selection_gpio = devm_gpiod_get(card->dev,
						     "tvout-selection",
						     GPIOD_OUT_LOW);
	if (IS_ERR(pdata->tvout_selection_gpio)) {
		dev_err(card->dev, "could not get tvout selection gpio\n");
		return PTR_ERR(pdata->tvout_selection_gpio);
	}

	pdata->jack_detection_gpio = devm_gpiod_get(card->dev,
						    "jack-detection",
						    GPIOD_ASIS);
	if (IS_ERR(pdata->jack_detection_gpio)) {
		dev_err(card->dev, "could not get jack detection gpio\n");
		return PTR_ERR(pdata->jack_detection_gpio);
	}

	pdata->eci_sw_gpio = devm_gpiod_get(card->dev, "eci-switch",
					    GPIOD_OUT_HIGH);
	if (IS_ERR(pdata->eci_sw_gpio)) {
		dev_err(card->dev, "could not get eci switch gpio\n");
		return PTR_ERR(pdata->eci_sw_gpio);
	}

	pdata->speaker_amp_gpio = devm_gpiod_get(card->dev,
						 "speaker-amplifier",
						 GPIOD_OUT_LOW);
	if (IS_ERR(pdata->speaker_amp_gpio)) {
		dev_err(card->dev, "could not get speaker enable gpio\n");
		return PTR_ERR(pdata->speaker_amp_gpio);
	}

	err = devm_snd_soc_register_card(card->dev, card);
	if (err) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", err);
		return err;
	}

	return 0;
}