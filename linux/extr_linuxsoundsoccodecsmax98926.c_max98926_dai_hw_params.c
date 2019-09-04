#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max98926_priv {int ch_size; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int rate; int sr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int MAX98926_DAI_BSEL_32 ; 
 int MAX98926_DAI_BSEL_48 ; 
 int MAX98926_DAI_BSEL_64 ; 
 int /*<<< orphan*/  MAX98926_DAI_BSEL_MASK ; 
 int MAX98926_DAI_CHANSZ_16 ; 
 int MAX98926_DAI_CHANSZ_24 ; 
 int MAX98926_DAI_CHANSZ_32 ; 
 int /*<<< orphan*/  MAX98926_DAI_CHANSZ_MASK ; 
 int /*<<< orphan*/  MAX98926_DAI_CLK_MODE2 ; 
 int /*<<< orphan*/  MAX98926_DAI_SR_MASK ; 
 int MAX98926_DAI_SR_SHIFT ; 
 int /*<<< orphan*/  MAX98926_FORMAT ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 TYPE_1__* rate_table ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98926_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98926_dai_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	int dai_sr = -EINVAL;
	int rate = params_rate(params), i;
	struct snd_soc_component *component = dai->component;
	struct max98926_priv *max98926 = snd_soc_component_get_drvdata(component);
	int blr_clk_ratio;

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_CHANSZ_MASK,
			MAX98926_DAI_CHANSZ_16);
		max98926->ch_size = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_CHANSZ_MASK,
			MAX98926_DAI_CHANSZ_24);
		max98926->ch_size = 24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		regmap_update_bits(max98926->regmap,
			MAX98926_FORMAT,
			MAX98926_DAI_CHANSZ_MASK,
			MAX98926_DAI_CHANSZ_32);
		max98926->ch_size = 32;
		break;
	default:
		dev_dbg(component->dev, "format unsupported %d\n",
			params_format(params));
		return -EINVAL;
	}

	/* BCLK/LRCLK ratio calculation */
	blr_clk_ratio = params_channels(params) * max98926->ch_size;

	switch (blr_clk_ratio) {
	case 32:
		regmap_update_bits(max98926->regmap,
			MAX98926_DAI_CLK_MODE2,
			MAX98926_DAI_BSEL_MASK,
			MAX98926_DAI_BSEL_32);
		break;
	case 48:
		regmap_update_bits(max98926->regmap,
			MAX98926_DAI_CLK_MODE2,
			MAX98926_DAI_BSEL_MASK,
			MAX98926_DAI_BSEL_48);
		break;
	case 64:
		regmap_update_bits(max98926->regmap,
			MAX98926_DAI_CLK_MODE2,
			MAX98926_DAI_BSEL_MASK,
			MAX98926_DAI_BSEL_64);
		break;
	default:
		return -EINVAL;
	}

	/* find the closest rate */
	for (i = 0; i < ARRAY_SIZE(rate_table); i++) {
		if (rate_table[i].rate >= rate) {
			dai_sr = rate_table[i].sr;
			break;
		}
	}
	if (dai_sr < 0)
		return -EINVAL;

	/* set DAI_SR to correct LRCLK frequency */
	regmap_update_bits(max98926->regmap,
		MAX98926_DAI_CLK_MODE2,
		MAX98926_DAI_SR_MASK, dai_sr << MAX98926_DAI_SR_SHIFT);
	return 0;
}