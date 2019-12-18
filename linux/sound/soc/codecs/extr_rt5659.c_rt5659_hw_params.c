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
struct snd_soc_dai {size_t id; int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct rt5659_priv {int* lrck; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5659_ADDA_CLK_1 ; 
#define  RT5659_AIF1 130 
#define  RT5659_AIF2 129 
#define  RT5659_AIF3 128 
 unsigned int RT5659_DAC_OSR_128 ; 
 unsigned int RT5659_DAC_OSR_32 ; 
 unsigned int RT5659_DAC_OSR_64 ; 
 unsigned int RT5659_DAC_OSR_MASK ; 
 int /*<<< orphan*/  RT5659_I2S1_SDP ; 
 int /*<<< orphan*/  RT5659_I2S2_SDP ; 
 int /*<<< orphan*/  RT5659_I2S3_SDP ; 
 unsigned int RT5659_I2S_DL_20 ; 
 unsigned int RT5659_I2S_DL_24 ; 
 unsigned int RT5659_I2S_DL_8 ; 
 unsigned int RT5659_I2S_DL_MASK ; 
 unsigned int RT5659_I2S_PD1_MASK ; 
 int RT5659_I2S_PD1_SFT ; 
 unsigned int RT5659_I2S_PD2_MASK ; 
 int RT5659_I2S_PD2_SFT ; 
 unsigned int RT5659_I2S_PD3_MASK ; 
 int RT5659_I2S_PD3_SFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int rl6231_get_clk_info (int /*<<< orphan*/ ,int) ; 
 struct rt5659_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int rt5659_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct rt5659_priv *rt5659 = snd_soc_component_get_drvdata(component);
	unsigned int val_len = 0, val_clk, mask_clk;
	int pre_div, frame_size;

	rt5659->lrck[dai->id] = params_rate(params);
	pre_div = rl6231_get_clk_info(rt5659->sysclk, rt5659->lrck[dai->id]);
	if (pre_div < 0) {
		dev_err(component->dev, "Unsupported clock setting %d for DAI %d\n",
			rt5659->lrck[dai->id], dai->id);
		return -EINVAL;
	}
	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0) {
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		return -EINVAL;
	}

	dev_dbg(dai->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt5659->lrck[dai->id], pre_div, dai->id);

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		val_len |= RT5659_I2S_DL_20;
		break;
	case 24:
		val_len |= RT5659_I2S_DL_24;
		break;
	case 8:
		val_len |= RT5659_I2S_DL_8;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT5659_AIF1:
		mask_clk = RT5659_I2S_PD1_MASK;
		val_clk = pre_div << RT5659_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5659_I2S1_SDP,
			RT5659_I2S_DL_MASK, val_len);
		break;
	case RT5659_AIF2:
		mask_clk = RT5659_I2S_PD2_MASK;
		val_clk = pre_div << RT5659_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5659_I2S2_SDP,
			RT5659_I2S_DL_MASK, val_len);
		break;
	case RT5659_AIF3:
		mask_clk = RT5659_I2S_PD3_MASK;
		val_clk = pre_div << RT5659_I2S_PD3_SFT;
		snd_soc_component_update_bits(component, RT5659_I2S3_SDP,
			RT5659_I2S_DL_MASK, val_len);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1, mask_clk, val_clk);

	switch (rt5659->lrck[dai->id]) {
	case 192000:
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_DAC_OSR_MASK, RT5659_DAC_OSR_32);
		break;
	case 96000:
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_DAC_OSR_MASK, RT5659_DAC_OSR_64);
		break;
	default:
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_DAC_OSR_MASK, RT5659_DAC_OSR_128);
		break;
	}

	return 0;
}