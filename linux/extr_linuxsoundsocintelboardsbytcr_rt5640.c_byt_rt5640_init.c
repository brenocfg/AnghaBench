#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_dapm_route {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_7__ {int idle_bias_off; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_2__ dapm; } ;
struct TYPE_8__ {int /*<<< orphan*/  jack; } ;
struct byt_rt5640_private {TYPE_4__ jack; int /*<<< orphan*/  mclk; } ;
struct TYPE_6__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct snd_soc_dapm_route const*) ; 
#define  BYT_RT5640_DMIC2_MAP 130 
#define  BYT_RT5640_IN1_MAP 129 
#define  BYT_RT5640_IN3_MAP 128 
 scalar_t__ BYT_RT5640_JDSRC (int) ; 
 int BYT_RT5640_MAP (int) ; 
 int BYT_RT5640_MCLK_25MHZ ; 
 int BYT_RT5640_MCLK_EN ; 
 int BYT_RT5640_MONO_SPEAKER ; 
 int BYT_RT5640_SSP0_AIF1 ; 
 int BYT_RT5640_SSP0_AIF2 ; 
 int BYT_RT5640_SSP2_AIF2 ; 
 int /*<<< orphan*/  KEY_PLAYPAUSE ; 
 int RT5640_AD_MONO_L_FILTER ; 
 int RT5640_AD_MONO_R_FILTER ; 
 int RT5640_AD_STEREO_FILTER ; 
 int /*<<< orphan*/  RT5640_CLK_SEL_ASRC ; 
 int RT5640_DA_MONO_L_FILTER ; 
 int RT5640_DA_MONO_R_FILTER ; 
 int RT5640_DA_STEREO_FILTER ; 
 int /*<<< orphan*/  RT5640_GLB_CLK ; 
 int /*<<< orphan*/  RT5640_SCLK_SRC_MASK ; 
 int /*<<< orphan*/  RT5640_SCLK_SRC_RCCLK ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_HEADSET ; 
 struct snd_soc_dapm_route const* byt_rt5640_controls ; 
 struct snd_soc_dapm_route const* byt_rt5640_intmic_dmic1_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_intmic_dmic2_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_intmic_in1_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_intmic_in3_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_mono_spk_map ; 
 int byt_rt5640_quirk ; 
 struct snd_soc_dapm_route const* byt_rt5640_ssp0_aif1_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_ssp0_aif2_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_ssp2_aif1_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_ssp2_aif2_map ; 
 struct snd_soc_dapm_route const* byt_rt5640_stereo_spk_map ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct snd_soc_dapm_route const* rt5640_pins ; 
 int /*<<< orphan*/  rt5640_sel_asrc_clk_src (struct snd_soc_component*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_jack_set_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_add_card_controls (struct snd_soc_card*,struct snd_soc_dapm_route const*,int) ; 
 struct byt_rt5640_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,TYPE_4__*,struct snd_soc_dapm_route const*,int) ; 
 int /*<<< orphan*/  snd_soc_component_set_jack (struct snd_soc_component*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_add_routes (TYPE_2__*,struct snd_soc_dapm_route const*,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_ignore_suspend (TYPE_2__*,char*) ; 

__attribute__((used)) static int byt_rt5640_init(struct snd_soc_pcm_runtime *runtime)
{
	struct snd_soc_card *card = runtime->card;
	struct byt_rt5640_private *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_component *component = runtime->codec_dai->component;
	const struct snd_soc_dapm_route *custom_map;
	int num_routes;
	int ret;

	card->dapm.idle_bias_off = true;

	/* Start with RC clk for jack-detect (we disable MCLK below) */
	if (byt_rt5640_quirk & BYT_RT5640_MCLK_EN)
		snd_soc_component_update_bits(component, RT5640_GLB_CLK,
			RT5640_SCLK_SRC_MASK, RT5640_SCLK_SRC_RCCLK);

	rt5640_sel_asrc_clk_src(component,
				RT5640_DA_STEREO_FILTER |
				RT5640_DA_MONO_L_FILTER	|
				RT5640_DA_MONO_R_FILTER	|
				RT5640_AD_STEREO_FILTER	|
				RT5640_AD_MONO_L_FILTER	|
				RT5640_AD_MONO_R_FILTER,
				RT5640_CLK_SEL_ASRC);

	ret = snd_soc_add_card_controls(card, byt_rt5640_controls,
					ARRAY_SIZE(byt_rt5640_controls));
	if (ret) {
		dev_err(card->dev, "unable to add card controls\n");
		return ret;
	}

	switch (BYT_RT5640_MAP(byt_rt5640_quirk)) {
	case BYT_RT5640_IN1_MAP:
		custom_map = byt_rt5640_intmic_in1_map;
		num_routes = ARRAY_SIZE(byt_rt5640_intmic_in1_map);
		break;
	case BYT_RT5640_IN3_MAP:
		custom_map = byt_rt5640_intmic_in3_map;
		num_routes = ARRAY_SIZE(byt_rt5640_intmic_in3_map);
		break;
	case BYT_RT5640_DMIC2_MAP:
		custom_map = byt_rt5640_intmic_dmic2_map;
		num_routes = ARRAY_SIZE(byt_rt5640_intmic_dmic2_map);
		break;
	default:
		custom_map = byt_rt5640_intmic_dmic1_map;
		num_routes = ARRAY_SIZE(byt_rt5640_intmic_dmic1_map);
	}

	ret = snd_soc_dapm_add_routes(&card->dapm, custom_map, num_routes);
	if (ret)
		return ret;

	if (byt_rt5640_quirk & BYT_RT5640_SSP2_AIF2) {
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp2_aif2_map,
					ARRAY_SIZE(byt_rt5640_ssp2_aif2_map));
	} else if (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) {
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp0_aif1_map,
					ARRAY_SIZE(byt_rt5640_ssp0_aif1_map));
	} else if (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2) {
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp0_aif2_map,
					ARRAY_SIZE(byt_rt5640_ssp0_aif2_map));
	} else {
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_ssp2_aif1_map,
					ARRAY_SIZE(byt_rt5640_ssp2_aif1_map));
	}
	if (ret)
		return ret;

	if (byt_rt5640_quirk & BYT_RT5640_MONO_SPEAKER) {
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_mono_spk_map,
					ARRAY_SIZE(byt_rt5640_mono_spk_map));
	} else {
		ret = snd_soc_dapm_add_routes(&card->dapm,
					byt_rt5640_stereo_spk_map,
					ARRAY_SIZE(byt_rt5640_stereo_spk_map));
	}
	if (ret)
		return ret;

	snd_soc_dapm_ignore_suspend(&card->dapm, "Headphone");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Speaker");

	if (byt_rt5640_quirk & BYT_RT5640_MCLK_EN) {
		/*
		 * The firmware might enable the clock at
		 * boot (this information may or may not
		 * be reflected in the enable clock register).
		 * To change the rate we must disable the clock
		 * first to cover these cases. Due to common
		 * clock framework restrictions that do not allow
		 * to disable a clock that has not been enabled,
		 * we need to enable the clock first.
		 */
		ret = clk_prepare_enable(priv->mclk);
		if (!ret)
			clk_disable_unprepare(priv->mclk);

		if (byt_rt5640_quirk & BYT_RT5640_MCLK_25MHZ)
			ret = clk_set_rate(priv->mclk, 25000000);
		else
			ret = clk_set_rate(priv->mclk, 19200000);

		if (ret) {
			dev_err(card->dev, "unable to set MCLK rate\n");
			return ret;
		}
	}

	if (BYT_RT5640_JDSRC(byt_rt5640_quirk)) {
		ret = snd_soc_card_jack_new(card, "Headset",
					    SND_JACK_HEADSET | SND_JACK_BTN_0,
					    &priv->jack, rt5640_pins,
					    ARRAY_SIZE(rt5640_pins));
		if (ret) {
			dev_err(card->dev, "Jack creation failed %d\n", ret);
			return ret;
		}
		snd_jack_set_key(priv->jack.jack, SND_JACK_BTN_0,
				 KEY_PLAYPAUSE);
		snd_soc_component_set_jack(component, &priv->jack, NULL);
	}

	return 0;
}