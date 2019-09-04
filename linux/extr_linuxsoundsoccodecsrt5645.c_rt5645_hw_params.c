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
struct rt5645_priv {int* lrck; int codec_type; int* bclk; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
#define  CODEC_TYPE_RT5650 130 
 int EINVAL ; 
 int /*<<< orphan*/  RT5645_ADDA_CLK1 ; 
#define  RT5645_AIF1 129 
#define  RT5645_AIF2 128 
 int /*<<< orphan*/  RT5645_I2S1_SDP ; 
 int /*<<< orphan*/  RT5645_I2S2_SDP ; 
 unsigned int RT5645_I2S_BCLK_MS2_MASK ; 
 int RT5645_I2S_BCLK_MS2_SFT ; 
 unsigned int RT5645_I2S_PD1_MASK ; 
 int RT5645_I2S_PD1_SFT ; 
 unsigned int RT5645_I2S_PD2_MASK ; 
 int RT5645_I2S_PD2_SFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int rl6231_get_clk_info (int /*<<< orphan*/ ,int) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int rt5645_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	unsigned int val_len = 0, val_clk, mask_clk, dl_sft;
	int pre_div, bclk_ms, frame_size;

	rt5645->lrck[dai->id] = params_rate(params);
	pre_div = rl6231_get_clk_info(rt5645->sysclk, rt5645->lrck[dai->id]);
	if (pre_div < 0) {
		dev_err(component->dev, "Unsupported clock setting\n");
		return -EINVAL;
	}
	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0) {
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		return -EINVAL;
	}

	switch (rt5645->codec_type) {
	case CODEC_TYPE_RT5650:
		dl_sft = 4;
		break;
	default:
		dl_sft = 2;
		break;
	}

	bclk_ms = frame_size > 32;
	rt5645->bclk[dai->id] = rt5645->lrck[dai->id] * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt5645->bclk[dai->id], rt5645->lrck[dai->id]);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_div, dai->id);

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		val_len = 0x1;
		break;
	case 24:
		val_len = 0x2;
		break;
	case 8:
		val_len = 0x3;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT5645_AIF1:
		mask_clk = RT5645_I2S_PD1_MASK;
		val_clk = pre_div << RT5645_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5645_I2S1_SDP,
			(0x3 << dl_sft), (val_len << dl_sft));
		snd_soc_component_update_bits(component, RT5645_ADDA_CLK1, mask_clk, val_clk);
		break;
	case  RT5645_AIF2:
		mask_clk = RT5645_I2S_BCLK_MS2_MASK | RT5645_I2S_PD2_MASK;
		val_clk = bclk_ms << RT5645_I2S_BCLK_MS2_SFT |
			pre_div << RT5645_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5645_I2S2_SDP,
			(0x3 << dl_sft), (val_len << dl_sft));
		snd_soc_component_update_bits(component, RT5645_ADDA_CLK1, mask_clk, val_clk);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}

	return 0;
}