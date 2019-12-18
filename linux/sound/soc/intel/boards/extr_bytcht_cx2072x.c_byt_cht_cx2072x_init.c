#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_2__* codec_dai; int /*<<< orphan*/  dev; struct snd_soc_card* card; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int idle_bias_off; } ;
struct snd_soc_card {TYPE_1__ dapm; } ;
struct TYPE_5__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX2072X_MCLK_EXTERNAL_PLL ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  byt_cht_cx2072x_acpi_gpios ; 
 int /*<<< orphan*/  byt_cht_cx2072x_headset ; 
 int /*<<< orphan*/  byt_cht_cx2072x_headset_pins ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ devm_acpi_dev_add_driver_gpios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_jack (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dai_set_bclk_ratio (TYPE_2__*,int) ; 
 int snd_soc_dai_set_sysclk (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_cht_cx2072x_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_component *codec = rtd->codec_dai->component;
	int ret;

	if (devm_acpi_dev_add_driver_gpios(codec->dev,
					   byt_cht_cx2072x_acpi_gpios))
		dev_warn(rtd->dev, "Unable to add GPIO mapping table\n");

	card->dapm.idle_bias_off = true;

	/* set the default PLL rate, the clock is handled by the codec driver */
	ret = snd_soc_dai_set_sysclk(rtd->codec_dai, CX2072X_MCLK_EXTERNAL_PLL,
				     19200000, SND_SOC_CLOCK_IN);
	if (ret) {
		dev_err(rtd->dev, "Could not set sysclk\n");
		return ret;
	}

	ret = snd_soc_card_jack_new(card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &byt_cht_cx2072x_headset,
				    byt_cht_cx2072x_headset_pins,
				    ARRAY_SIZE(byt_cht_cx2072x_headset_pins));
	if (ret)
		return ret;

	snd_soc_component_set_jack(codec, &byt_cht_cx2072x_headset, NULL);

	snd_soc_dai_set_bclk_ratio(rtd->codec_dai, 50);

	return ret;
}