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
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct adau {int clk_src; unsigned int pll_freq; unsigned int sysclk; scalar_t__ dai_fmt; int /*<<< orphan*/  regmap; scalar_t__ sigmadsp; } ;

/* Variables and functions */
#define  ADAU17X1_CLK_SRC_PLL 129 
#define  ADAU17X1_CLK_SRC_PLL_AUTO 128 
 int /*<<< orphan*/  ADAU17X1_CONVERTER0 ; 
 int /*<<< orphan*/  ADAU17X1_CONVERTER0_CONVSR_MASK ; 
 int /*<<< orphan*/  ADAU17X1_DSP_SAMPLING_RATE ; 
 int /*<<< orphan*/  ADAU17X1_SERIAL_PORT1 ; 
 unsigned int ADAU17X1_SERIAL_PORT1_DELAY0 ; 
 unsigned int ADAU17X1_SERIAL_PORT1_DELAY16 ; 
 unsigned int ADAU17X1_SERIAL_PORT1_DELAY8 ; 
 int /*<<< orphan*/  ADAU17X1_SERIAL_PORT1_DELAY_MASK ; 
 int /*<<< orphan*/  ADAU17X1_SERIAL_SAMPLING_RATE ; 
 int EINVAL ; 
 scalar_t__ SND_SOC_DAIFMT_RIGHT_J ; 
 int adau17x1_auto_pll (struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 scalar_t__ adau17x1_has_dsp (struct adau*) ; 
 int adau17x1_setup_firmware (struct snd_soc_component*,unsigned int) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau17x1_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct adau *adau = snd_soc_component_get_drvdata(component);
	unsigned int val, div, dsp_div;
	unsigned int freq;
	int ret;

	switch (adau->clk_src) {
	case ADAU17X1_CLK_SRC_PLL_AUTO:
		ret = adau17x1_auto_pll(dai, params);
		if (ret)
			return ret;
		/* Fall-through */
	case ADAU17X1_CLK_SRC_PLL:
		freq = adau->pll_freq;
		break;
	default:
		freq = adau->sysclk;
		break;
	}

	if (freq % params_rate(params) != 0)
		return -EINVAL;

	switch (freq / params_rate(params)) {
	case 1024: /* fs */
		div = 0;
		dsp_div = 1;
		break;
	case 6144: /* fs / 6 */
		div = 1;
		dsp_div = 6;
		break;
	case 4096: /* fs / 4 */
		div = 2;
		dsp_div = 5;
		break;
	case 3072: /* fs / 3 */
		div = 3;
		dsp_div = 4;
		break;
	case 2048: /* fs / 2 */
		div = 4;
		dsp_div = 3;
		break;
	case 1536: /* fs / 1.5 */
		div = 5;
		dsp_div = 2;
		break;
	case 512: /* fs / 0.5 */
		div = 6;
		dsp_div = 0;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_CONVSR_MASK, div);
	if (adau17x1_has_dsp(adau)) {
		regmap_write(adau->regmap, ADAU17X1_SERIAL_SAMPLING_RATE, div);
		regmap_write(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, dsp_div);
	}

	if (adau->sigmadsp) {
		ret = adau17x1_setup_firmware(component, params_rate(params));
		if (ret < 0)
			return ret;
	}

	if (adau->dai_fmt != SND_SOC_DAIFMT_RIGHT_J)
		return 0;

	switch (params_width(params)) {
	case 16:
		val = ADAU17X1_SERIAL_PORT1_DELAY16;
		break;
	case 24:
		val = ADAU17X1_SERIAL_PORT1_DELAY8;
		break;
	case 32:
		val = ADAU17X1_SERIAL_PORT1_DELAY0;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT1,
			ADAU17X1_SERIAL_PORT1_DELAY_MASK, val);
}