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
struct rt5665_priv {int* lrck; scalar_t__* master; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int RT5665_ADC_OSR_128 ; 
 int RT5665_ADC_OSR_32 ; 
 int RT5665_ADC_OSR_64 ; 
 int RT5665_ADC_OSR_MASK ; 
 unsigned int RT5665_ADDA_CLK_1 ; 
 unsigned int RT5665_ADDA_CLK_2 ; 
#define  RT5665_AIF1_1 132 
#define  RT5665_AIF1_2 131 
#define  RT5665_AIF2_1 130 
#define  RT5665_AIF2_2 129 
#define  RT5665_AIF3 128 
 int RT5665_DAC_OSR_128 ; 
 int RT5665_DAC_OSR_32 ; 
 int RT5665_DAC_OSR_64 ; 
 int RT5665_DAC_OSR_MASK ; 
 unsigned int RT5665_I2S1_SDP ; 
 int RT5665_I2S2_M_PD_MASK ; 
 int RT5665_I2S2_M_PD_SFT ; 
 unsigned int RT5665_I2S2_SDP ; 
 int RT5665_I2S3_M_PD_MASK ; 
 int RT5665_I2S3_M_PD_SFT ; 
 unsigned int RT5665_I2S3_SDP ; 
 unsigned int RT5665_I2S_DL_20 ; 
 unsigned int RT5665_I2S_DL_24 ; 
 unsigned int RT5665_I2S_DL_8 ; 
 int RT5665_I2S_DL_MASK ; 
 unsigned int RT5665_I2S_M_CLK_CTRL_1 ; 
 unsigned int RT5665_I2S_PD1_MASK ; 
 int RT5665_I2S_PD1_SFT ; 
 unsigned int RT5665_I2S_PD2_MASK ; 
 int RT5665_I2S_PD2_SFT ; 
 unsigned int RT5665_I2S_PD3_MASK ; 
 int RT5665_I2S_PD3_SFT ; 
 int /*<<< orphan*/  RT5665_PLL1_S_MCLK ; 
 int /*<<< orphan*/  RT5665_SCLK_S_PLL1 ; 
 unsigned int RT5665_STO1_DAC_SIL_DET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int rl6231_get_clk_info (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt5665_set_tdm_slot (struct snd_soc_dai*,int,int,int,int) ; 
 struct rt5665_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,int) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int rt5665_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);
	unsigned int val_len = 0, val_clk, reg_clk, mask_clk, val_bits = 0x0100;
	int pre_div, frame_size;

	rt5665->lrck[dai->id] = params_rate(params);
	pre_div = rl6231_get_clk_info(rt5665->sysclk, rt5665->lrck[dai->id]);
	if (pre_div < 0) {
		dev_warn(component->dev, "Force using PLL");
		snd_soc_component_set_pll(component, 0, RT5665_PLL1_S_MCLK,
			rt5665->sysclk,	rt5665->lrck[dai->id] * 512);
		snd_soc_component_set_sysclk(component, RT5665_SCLK_S_PLL1, 0,
			rt5665->lrck[dai->id] * 512, 0);
		pre_div = 1;
	}
	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0) {
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		return -EINVAL;
	}

	dev_dbg(dai->dev, "lrck is %dHz and pre_div is %d for iis %d\n",
				rt5665->lrck[dai->id], pre_div, dai->id);

	switch (params_width(params)) {
	case 16:
		val_bits = 0x0100;
		break;
	case 20:
		val_len |= RT5665_I2S_DL_20;
		val_bits = 0x1300;
		break;
	case 24:
		val_len |= RT5665_I2S_DL_24;
		val_bits = 0x2500;
		break;
	case 8:
		val_len |= RT5665_I2S_DL_8;
		break;
	default:
		return -EINVAL;
	}

	switch (dai->id) {
	case RT5665_AIF1_1:
	case RT5665_AIF1_2:
		if (params_channels(params) > 2)
			rt5665_set_tdm_slot(dai, 0xf, 0xf,
				params_channels(params), params_width(params));
		reg_clk = RT5665_ADDA_CLK_1;
		mask_clk = RT5665_I2S_PD1_MASK;
		val_clk = pre_div << RT5665_I2S_PD1_SFT;
		snd_soc_component_update_bits(component, RT5665_I2S1_SDP,
			RT5665_I2S_DL_MASK, val_len);
		break;
	case RT5665_AIF2_1:
	case RT5665_AIF2_2:
		reg_clk = RT5665_ADDA_CLK_2;
		mask_clk = RT5665_I2S_PD2_MASK;
		val_clk = pre_div << RT5665_I2S_PD2_SFT;
		snd_soc_component_update_bits(component, RT5665_I2S2_SDP,
			RT5665_I2S_DL_MASK, val_len);
		break;
	case RT5665_AIF3:
		reg_clk = RT5665_ADDA_CLK_2;
		mask_clk = RT5665_I2S_PD3_MASK;
		val_clk = pre_div << RT5665_I2S_PD3_SFT;
		snd_soc_component_update_bits(component, RT5665_I2S3_SDP,
			RT5665_I2S_DL_MASK, val_len);
		break;
	default:
		dev_err(component->dev, "Invalid dai->id: %d\n", dai->id);
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, reg_clk, mask_clk, val_clk);
	snd_soc_component_update_bits(component, RT5665_STO1_DAC_SIL_DET, 0x3700, val_bits);

	switch (rt5665->lrck[dai->id]) {
	case 192000:
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_DAC_OSR_MASK | RT5665_ADC_OSR_MASK,
			RT5665_DAC_OSR_32 | RT5665_ADC_OSR_32);
		break;
	case 96000:
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_DAC_OSR_MASK | RT5665_ADC_OSR_MASK,
			RT5665_DAC_OSR_64 | RT5665_ADC_OSR_64);
		break;
	default:
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_DAC_OSR_MASK | RT5665_ADC_OSR_MASK,
			RT5665_DAC_OSR_128 | RT5665_ADC_OSR_128);
		break;
	}

	if (rt5665->master[RT5665_AIF2_1] || rt5665->master[RT5665_AIF2_2]) {
		snd_soc_component_update_bits(component, RT5665_I2S_M_CLK_CTRL_1,
			RT5665_I2S2_M_PD_MASK, pre_div << RT5665_I2S2_M_PD_SFT);
	}
	if (rt5665->master[RT5665_AIF3]) {
		snd_soc_component_update_bits(component, RT5665_I2S_M_CLK_CTRL_1,
			RT5665_I2S3_M_PD_MASK, pre_div << RT5665_I2S3_M_PD_SFT);
	}

	return 0;
}