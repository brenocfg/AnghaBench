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
struct snd_soc_dai {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct rt5514_priv {int lrck; int bclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int RT5514_CLK_AD_ANA1_SEL_MASK ; 
 int RT5514_CLK_AD_ANA1_SEL_SFT ; 
 int /*<<< orphan*/  RT5514_CLK_CTRL1 ; 
 int /*<<< orphan*/  RT5514_CLK_CTRL2 ; 
 int RT5514_CLK_SYS_DIV_OUT_MASK ; 
 int RT5514_CLK_SYS_DIV_OUT_SFT ; 
 int /*<<< orphan*/  RT5514_I2S_CTRL1 ; 
 unsigned int RT5514_I2S_DL_20 ; 
 unsigned int RT5514_I2S_DL_24 ; 
 unsigned int RT5514_I2S_DL_8 ; 
 int RT5514_I2S_DL_MASK ; 
 int RT5514_SEL_ADC_OSR_MASK ; 
 int RT5514_SEL_ADC_OSR_SFT ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int rl6231_get_clk_info (int /*<<< orphan*/ ,int) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int rt5514_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	int pre_div, bclk_ms, frame_size;
	unsigned int val_len = 0;

	rt5514->lrck = params_rate(params);
	pre_div = rl6231_get_clk_info(rt5514->sysclk, rt5514->lrck);
	if (pre_div < 0) {
		dev_err(component->dev, "Unsupported clock setting\n");
		return -EINVAL;
	}

	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0) {
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		return -EINVAL;
	}

	bclk_ms = frame_size > 32;
	rt5514->bclk = rt5514->lrck * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5514->bclk, rt5514->lrck);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_div, dai->id);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		val_len = RT5514_I2S_DL_20;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		val_len = RT5514_I2S_DL_24;
		break;
	case SNDRV_PCM_FORMAT_S8:
		val_len = RT5514_I2S_DL_8;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL1, RT5514_I2S_DL_MASK,
		val_len);
	regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL1,
		RT5514_CLK_AD_ANA1_SEL_MASK,
		(pre_div + 1) << RT5514_CLK_AD_ANA1_SEL_SFT);
	regmap_update_bits(rt5514->regmap, RT5514_CLK_CTRL2,
		RT5514_CLK_SYS_DIV_OUT_MASK | RT5514_SEL_ADC_OSR_MASK,
		pre_div << RT5514_CLK_SYS_DIV_OUT_SFT |
		pre_div << RT5514_SEL_ADC_OSR_SFT);

	return 0;
}