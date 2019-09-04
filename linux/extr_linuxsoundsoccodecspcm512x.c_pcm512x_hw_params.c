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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct pcm512x_priv {int fmt; int pll_out; int pll_in; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCM512x_ALEN ; 
 int PCM512x_ALEN_16 ; 
 int PCM512x_ALEN_20 ; 
 int PCM512x_ALEN_24 ; 
 int PCM512x_ALEN_32 ; 
 int PCM512x_BCKO ; 
 int PCM512x_BCKP ; 
 int PCM512x_BCLK_LRCLK_CFG ; 
 int PCM512x_DCAS ; 
 int PCM512x_ERROR_DETECT ; 
 int /*<<< orphan*/  PCM512x_FLEX_A ; 
 int /*<<< orphan*/  PCM512x_FLEX_B ; 
 int PCM512x_G1OE ; 
 int PCM512x_GPIO_EN ; 
 int PCM512x_GPIO_OUTPUT_1 ; 
 int PCM512x_GPIO_PLLIN ; 
 int PCM512x_GREF ; 
 int PCM512x_GREF_GPIO1 ; 
 int PCM512x_GxSL ; 
 int PCM512x_GxSL_PLLCK ; 
 int PCM512x_I2S_1 ; 
 int PCM512x_IDBK ; 
 int PCM512x_IDCH ; 
 int PCM512x_IDCM ; 
 int PCM512x_IDFS ; 
 int PCM512x_IDSK ; 
 int PCM512x_IPLK ; 
 int PCM512x_LRKO ; 
 int PCM512x_MASTER_MODE ; 
 int PCM512x_PLLE ; 
 int PCM512x_PLL_EN ; 
 int PCM512x_PLL_REF ; 
 int PCM512x_RBCK ; 
 int PCM512x_RLRK ; 
 int PCM512x_RQSY ; 
 int PCM512x_RQSY_HALT ; 
 int PCM512x_RQSY_RESUME ; 
 int PCM512x_SREF ; 
 int PCM512x_SREF_GPIO ; 
 int PCM512x_SYNCHRONIZE ; 
#define  SND_SOC_DAIFMT_CBM_CFM 130 
#define  SND_SOC_DAIFMT_CBM_CFS 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int pcm512x_set_dividers (struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm512x_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	int alen;
	int gpio;
	int clock_output;
	int master_mode;
	int ret;

	dev_dbg(component->dev, "hw_params %u Hz, %u channels\n",
		params_rate(params),
		params_channels(params));

	switch (params_width(params)) {
	case 16:
		alen = PCM512x_ALEN_16;
		break;
	case 20:
		alen = PCM512x_ALEN_20;
		break;
	case 24:
		alen = PCM512x_ALEN_24;
		break;
	case 32:
		alen = PCM512x_ALEN_32;
		break;
	default:
		dev_err(component->dev, "Bad frame size: %d\n",
			params_width(params));
		return -EINVAL;
	}

	switch (pcm512x->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		ret = regmap_update_bits(pcm512x->regmap,
					 PCM512x_BCLK_LRCLK_CFG,
					 PCM512x_BCKP
					 | PCM512x_BCKO | PCM512x_LRKO,
					 0);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to enable slave mode: %d\n", ret);
			return ret;
		}

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_ERROR_DETECT,
					 PCM512x_DCAS, 0);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to enable clock divider autoset: %d\n",
				ret);
			return ret;
		}
		return 0;
	case SND_SOC_DAIFMT_CBM_CFM:
		clock_output = PCM512x_BCKO | PCM512x_LRKO;
		master_mode = PCM512x_RLRK | PCM512x_RBCK;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		clock_output = PCM512x_BCKO;
		master_mode = PCM512x_RBCK;
		break;
	default:
		return -EINVAL;
	}

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_I2S_1,
				 PCM512x_ALEN, alen);
	if (ret != 0) {
		dev_err(component->dev, "Failed to set frame size: %d\n", ret);
		return ret;
	}

	if (pcm512x->pll_out) {
		ret = regmap_write(pcm512x->regmap, PCM512x_FLEX_A, 0x11);
		if (ret != 0) {
			dev_err(component->dev, "Failed to set FLEX_A: %d\n", ret);
			return ret;
		}

		ret = regmap_write(pcm512x->regmap, PCM512x_FLEX_B, 0xff);
		if (ret != 0) {
			dev_err(component->dev, "Failed to set FLEX_B: %d\n", ret);
			return ret;
		}

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_ERROR_DETECT,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_IDCM | PCM512x_DCAS
					 | PCM512x_IPLK,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_DCAS);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to ignore auto-clock failures: %d\n",
				ret);
			return ret;
		}
	} else {
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_ERROR_DETECT,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_IDCM | PCM512x_DCAS
					 | PCM512x_IPLK,
					 PCM512x_IDFS | PCM512x_IDBK
					 | PCM512x_IDSK | PCM512x_IDCH
					 | PCM512x_DCAS | PCM512x_IPLK);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to ignore auto-clock failures: %d\n",
				ret);
			return ret;
		}

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_PLL_EN,
					 PCM512x_PLLE, 0);
		if (ret != 0) {
			dev_err(component->dev, "Failed to disable pll: %d\n", ret);
			return ret;
		}
	}

	ret = pcm512x_set_dividers(dai, params);
	if (ret != 0)
		return ret;

	if (pcm512x->pll_out) {
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_PLL_REF,
					 PCM512x_SREF, PCM512x_SREF_GPIO);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to set gpio as pllref: %d\n", ret);
			return ret;
		}

		gpio = PCM512x_GREF_GPIO1 + pcm512x->pll_in - 1;
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_GPIO_PLLIN,
					 PCM512x_GREF, gpio);
		if (ret != 0) {
			dev_err(component->dev,
				"Failed to set gpio %d as pllin: %d\n",
				pcm512x->pll_in, ret);
			return ret;
		}

		ret = regmap_update_bits(pcm512x->regmap, PCM512x_PLL_EN,
					 PCM512x_PLLE, PCM512x_PLLE);
		if (ret != 0) {
			dev_err(component->dev, "Failed to enable pll: %d\n", ret);
			return ret;
		}
	}

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_BCLK_LRCLK_CFG,
				 PCM512x_BCKP | PCM512x_BCKO | PCM512x_LRKO,
				 clock_output);
	if (ret != 0) {
		dev_err(component->dev, "Failed to enable clock output: %d\n", ret);
		return ret;
	}

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_MASTER_MODE,
				 PCM512x_RLRK | PCM512x_RBCK,
				 master_mode);
	if (ret != 0) {
		dev_err(component->dev, "Failed to enable master mode: %d\n", ret);
		return ret;
	}

	if (pcm512x->pll_out) {
		gpio = PCM512x_G1OE << (pcm512x->pll_out - 1);
		ret = regmap_update_bits(pcm512x->regmap, PCM512x_GPIO_EN,
					 gpio, gpio);
		if (ret != 0) {
			dev_err(component->dev, "Failed to enable gpio %d: %d\n",
				pcm512x->pll_out, ret);
			return ret;
		}

		gpio = PCM512x_GPIO_OUTPUT_1 + pcm512x->pll_out - 1;
		ret = regmap_update_bits(pcm512x->regmap, gpio,
					 PCM512x_GxSL, PCM512x_GxSL_PLLCK);
		if (ret != 0) {
			dev_err(component->dev, "Failed to output pll on %d: %d\n",
				ret, pcm512x->pll_out);
			return ret;
		}
	}

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_SYNCHRONIZE,
				 PCM512x_RQSY, PCM512x_RQSY_HALT);
	if (ret != 0) {
		dev_err(component->dev, "Failed to halt clocks: %d\n", ret);
		return ret;
	}

	ret = regmap_update_bits(pcm512x->regmap, PCM512x_SYNCHRONIZE,
				 PCM512x_RQSY, PCM512x_RQSY_RESUME);
	if (ret != 0) {
		dev_err(component->dev, "Failed to resume clocks: %d\n", ret);
		return ret;
	}

	return 0;
}