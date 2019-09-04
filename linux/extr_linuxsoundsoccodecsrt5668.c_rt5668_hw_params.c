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
struct rt5668_priv {int /*<<< orphan*/ * master; int /*<<< orphan*/ * lrck; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5668_ADDA_CLK_1 ; 
#define  RT5668_AIF1 129 
#define  RT5668_AIF2 128 
 unsigned int RT5668_I2S1_DL_20 ; 
 unsigned int RT5668_I2S1_DL_24 ; 
 unsigned int RT5668_I2S1_DL_32 ; 
 int /*<<< orphan*/  RT5668_I2S1_DL_MASK ; 
 int RT5668_I2S1_MONO_DIS ; 
 int RT5668_I2S1_MONO_EN ; 
 int /*<<< orphan*/  RT5668_I2S1_MONO_MASK ; 
 int /*<<< orphan*/  RT5668_I2S1_SDP ; 
 unsigned int RT5668_I2S2_DL_20 ; 
 unsigned int RT5668_I2S2_DL_24 ; 
 unsigned int RT5668_I2S2_DL_8 ; 
 int /*<<< orphan*/  RT5668_I2S2_DL_MASK ; 
 int RT5668_I2S2_MONO_DIS ; 
 int RT5668_I2S2_MONO_EN ; 
 int /*<<< orphan*/  RT5668_I2S2_MONO_MASK ; 
 int /*<<< orphan*/  RT5668_I2S2_M_PD_MASK ; 
 int RT5668_I2S2_M_PD_SFT ; 
 int /*<<< orphan*/  RT5668_I2S2_SDP ; 
 int /*<<< orphan*/  RT5668_I2S_M_CLK_CTRL_1 ; 
 int /*<<< orphan*/  RT5668_I2S_M_DIV_MASK ; 
 int RT5668_I2S_M_DIV_SFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int rl6231_get_clk_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt5668_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int rt5668_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct rt5668_priv *rt5668 = snd_soc_component_get_drvdata(component);
	unsigned int len_1 = 0, len_2 = 0;
	int pre_div, frame_size;

	rt5668->lrck[dai->id] = params_rate(params);
	pre_div = rl6231_get_clk_info(rt5668->sysclk, rt5668->lrck[dai->id]);

	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0) {
		dev_err(component->dev, "Unsupported frame size: %d\n",
			frame_size);
		return -EINVAL;
	}

	dev_dbg(dai->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt5668->lrck[dai->id], pre_div, dai->id);

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		len_1 |= RT5668_I2S1_DL_20;
		len_2 |= RT5668_I2S2_DL_20;
		break;
	case 24:
		len_1 |= RT5668_I2S1_DL_24;
		len_2 |= RT5668_I2S2_DL_24;
		break;
	case 32:
		len_1 |= RT5668_I2S1_DL_32;
		len_2 |= RT5668_I2S2_DL_24;
		break;
	case 8:
		len_1 |= RT5668_I2S2_DL_8;
		len_2 |= RT5668_I2S2_DL_8;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT5668_AIF1:
		snd_soc_component_update_bits(component, RT5668_I2S1_SDP,
			RT5668_I2S1_DL_MASK, len_1);
		if (rt5668->master[RT5668_AIF1]) {
			snd_soc_component_update_bits(component,
				RT5668_ADDA_CLK_1, RT5668_I2S_M_DIV_MASK,
				pre_div << RT5668_I2S_M_DIV_SFT);
		}
		if (params_channels(params) == 1) /* mono mode */
			snd_soc_component_update_bits(component,
				RT5668_I2S1_SDP, RT5668_I2S1_MONO_MASK,
				RT5668_I2S1_MONO_EN);
		else
			snd_soc_component_update_bits(component,
				RT5668_I2S1_SDP, RT5668_I2S1_MONO_MASK,
				RT5668_I2S1_MONO_DIS);
		break;
	case RT5668_AIF2:
		snd_soc_component_update_bits(component, RT5668_I2S2_SDP,
			RT5668_I2S2_DL_MASK, len_2);
		if (rt5668->master[RT5668_AIF2]) {
			snd_soc_component_update_bits(component,
				RT5668_I2S_M_CLK_CTRL_1, RT5668_I2S2_M_PD_MASK,
				pre_div << RT5668_I2S2_M_PD_SFT);
		}
		if (params_channels(params) == 1) /* mono mode */
			snd_soc_component_update_bits(component,
				RT5668_I2S2_SDP, RT5668_I2S2_MONO_MASK,
				RT5668_I2S2_MONO_EN);
		else
			snd_soc_component_update_bits(component,
				RT5668_I2S2_SDP, RT5668_I2S2_MONO_MASK,
				RT5668_I2S2_MONO_DIS);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}

	return 0;
}