#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_2__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_dapm_route {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_5__ {int idle_bias_off; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_1__ dapm; } ;
struct TYPE_7__ {int /*<<< orphan*/  jack; } ;
struct byt_cht_es8316_private {TYPE_3__ jack; int /*<<< orphan*/  mclk; } ;
struct TYPE_6__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct snd_soc_dapm_route*) ; 
#define  BYT_CHT_ES8316_INTMIC_IN1_MAP 129 
#define  BYT_CHT_ES8316_INTMIC_IN2_MAP 128 
 int BYT_CHT_ES8316_MAP (int) ; 
 int BYT_CHT_ES8316_SSP0 ; 
 int /*<<< orphan*/  KEY_PLAYPAUSE ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 struct snd_soc_dapm_route* byt_cht_es8316_intmic_in1_map ; 
 struct snd_soc_dapm_route* byt_cht_es8316_intmic_in2_map ; 
 struct snd_soc_dapm_route* byt_cht_es8316_jack_pins ; 
 struct snd_soc_dapm_route* byt_cht_es8316_ssp0_map ; 
 struct snd_soc_dapm_route* byt_cht_es8316_ssp2_map ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int quirk ; 
 int /*<<< orphan*/  snd_jack_set_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct byt_cht_es8316_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,TYPE_3__*,struct snd_soc_dapm_route*,int) ; 
 int /*<<< orphan*/  snd_soc_component_set_jack (struct snd_soc_component*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int snd_soc_dai_set_sysclk (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_add_routes (TYPE_1__*,struct snd_soc_dapm_route const*,int) ; 

__attribute__((used)) static int byt_cht_es8316_init(struct snd_soc_pcm_runtime *runtime)
{
	struct snd_soc_component *codec = runtime->codec_dai->component;
	struct snd_soc_card *card = runtime->card;
	struct byt_cht_es8316_private *priv = snd_soc_card_get_drvdata(card);
	const struct snd_soc_dapm_route *custom_map;
	int num_routes;
	int ret;

	card->dapm.idle_bias_off = true;

	switch (BYT_CHT_ES8316_MAP(quirk)) {
	case BYT_CHT_ES8316_INTMIC_IN1_MAP:
	default:
		custom_map = byt_cht_es8316_intmic_in1_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_intmic_in1_map);
		break;
	case BYT_CHT_ES8316_INTMIC_IN2_MAP:
		custom_map = byt_cht_es8316_intmic_in2_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_intmic_in2_map);
		break;
	}
	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	if (ret)
		return ret;

	if (quirk & BYT_CHT_ES8316_SSP0) {
		custom_map = byt_cht_es8316_ssp0_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_ssp0_map);
	} else {
		custom_map = byt_cht_es8316_ssp2_map;
		num_routes = ARRAY_SIZE(byt_cht_es8316_ssp2_map);
	}
	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	if (ret)
		return ret;

	/*
	 * The firmware might enable the clock at boot (this information
	 * may or may not be reflected in the enable clock register).
	 * To change the rate we must disable the clock first to cover these
	 * cases. Due to common clock framework restrictions that do not allow
	 * to disable a clock that has not been enabled, we need to enable
	 * the clock first.
	 */
	ret = clk_prepare_enable(priv->mclk);
	if (!ret)
		clk_disable_unprepare(priv->mclk);

	ret = clk_set_rate(priv->mclk, 19200000);
	if (ret)
		dev_err(card->dev, "unable to set MCLK rate\n");

	ret = clk_prepare_enable(priv->mclk);
	if (ret)
		dev_err(card->dev, "unable to enable MCLK\n");

	ret = snd_soc_dai_set_sysclk(runtime->codec_dai, 0, 19200000,
				     SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(card->dev, "can't set codec clock %d\n", ret);
		return ret;
	}

	ret = snd_soc_card_jack_new(card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &priv->jack, byt_cht_es8316_jack_pins,
				    ARRAY_SIZE(byt_cht_es8316_jack_pins));
	if (ret) {
		dev_err(card->dev, "jack creation failed %d\n", ret);
		return ret;
	}

	snd_jack_set_key(priv->jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_soc_component_set_jack(codec, &priv->jack, NULL);

	return 0;
}