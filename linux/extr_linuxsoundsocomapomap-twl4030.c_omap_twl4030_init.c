#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; struct snd_soc_dapm_context dapm; } ;
struct omap_twl4030 {scalar_t__ jack_detect; int /*<<< orphan*/  hs_jack; } ;
struct omap_tw4030_pdata {int /*<<< orphan*/  has_linein; int /*<<< orphan*/  has_digimic1; int /*<<< orphan*/  has_digimic0; int /*<<< orphan*/  has_carkitmic; int /*<<< orphan*/  has_hsmic; int /*<<< orphan*/  has_submic; int /*<<< orphan*/  has_mainmic; int /*<<< orphan*/  has_carkit; int /*<<< orphan*/  has_predriv; int /*<<< orphan*/  has_hs; int /*<<< orphan*/  has_hf; int /*<<< orphan*/  has_ear; int /*<<< orphan*/  custom_routing; } ;
struct TYPE_6__ {scalar_t__ gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 struct omap_tw4030_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 TYPE_1__* hs_jack_gpios ; 
 TYPE_1__* hs_jack_pins ; 
 struct omap_twl4030* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  twl4030_disconnect_pin (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int omap_twl4030_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_dapm_context *dapm = &card->dapm;
	struct omap_tw4030_pdata *pdata = dev_get_platdata(card->dev);
	struct omap_twl4030 *priv = snd_soc_card_get_drvdata(card);
	int ret = 0;

	/* Headset jack detection only if it is supported */
	if (priv->jack_detect > 0) {
		hs_jack_gpios[0].gpio = priv->jack_detect;

		ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
					    SND_JACK_HEADSET, &priv->hs_jack,
					    hs_jack_pins,
					    ARRAY_SIZE(hs_jack_pins));
		if (ret)
			return ret;

		ret = snd_soc_jack_add_gpios(&priv->hs_jack,
					     ARRAY_SIZE(hs_jack_gpios),
					     hs_jack_gpios);
		if (ret)
			return ret;
	}

	/*
	 * NULL pdata means we booted with DT. In this case the routing is
	 * provided and the card is fully routed, no need to mark pins.
	 */
	if (!pdata || !pdata->custom_routing)
		return ret;

	/* Disable not connected paths if not used */
	twl4030_disconnect_pin(dapm, pdata->has_ear, "Earpiece Spk");
	twl4030_disconnect_pin(dapm, pdata->has_hf, "Handsfree Spk");
	twl4030_disconnect_pin(dapm, pdata->has_hs, "Headset Stereophone");
	twl4030_disconnect_pin(dapm, pdata->has_predriv, "Ext Spk");
	twl4030_disconnect_pin(dapm, pdata->has_carkit, "Carkit Spk");

	twl4030_disconnect_pin(dapm, pdata->has_mainmic, "Main Mic");
	twl4030_disconnect_pin(dapm, pdata->has_submic, "Sub Mic");
	twl4030_disconnect_pin(dapm, pdata->has_hsmic, "Headset Mic");
	twl4030_disconnect_pin(dapm, pdata->has_carkitmic, "Carkit Mic");
	twl4030_disconnect_pin(dapm, pdata->has_digimic0, "Digital0 Mic");
	twl4030_disconnect_pin(dapm, pdata->has_digimic1, "Digital1 Mic");
	twl4030_disconnect_pin(dapm, pdata->has_linein, "Line In");

	return ret;
}