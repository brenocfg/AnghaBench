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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct rx51_audio_pdata {int /*<<< orphan*/  jack_detection_gpio; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_VIDEOOUT ; 
 int /*<<< orphan*/  desc_to_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_gpiod_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_mcbsp_st_add_controls (struct snd_soc_pcm_runtime*,int) ; 
 int /*<<< orphan*/  rx51_av_jack ; 
 TYPE_1__* rx51_av_jack_gpios ; 
 struct rx51_audio_pdata* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_limit_volume (struct snd_soc_card*,char*,int) ; 

__attribute__((used)) static int rx51_aic34_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct rx51_audio_pdata *pdata = snd_soc_card_get_drvdata(card);
	int err;

	snd_soc_limit_volume(card, "TPA6130A2 Headphone Playback Volume", 42);

	err = omap_mcbsp_st_add_controls(rtd, 2);
	if (err < 0) {
		dev_err(card->dev, "Failed to add MCBSP controls\n");
		return err;
	}

	/* AV jack detection */
	err = snd_soc_card_jack_new(rtd->card, "AV Jack",
				    SND_JACK_HEADSET | SND_JACK_VIDEOOUT,
				    &rx51_av_jack, NULL, 0);
	if (err) {
		dev_err(card->dev, "Failed to add AV Jack\n");
		return err;
	}

	/* prepare gpio for snd_soc_jack_add_gpios */
	rx51_av_jack_gpios[0].gpio = desc_to_gpio(pdata->jack_detection_gpio);
	devm_gpiod_put(card->dev, pdata->jack_detection_gpio);

	err = snd_soc_jack_add_gpios(&rx51_av_jack,
				     ARRAY_SIZE(rx51_av_jack_gpios),
				     rx51_av_jack_gpios);
	if (err) {
		dev_err(card->dev, "Failed to add GPIOs\n");
		return err;
	}

	return err;
}