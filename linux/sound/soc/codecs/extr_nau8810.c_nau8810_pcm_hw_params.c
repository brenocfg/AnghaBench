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
struct nau8810 {scalar_t__ clk_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NAU8810_BCLKDIV_2 ; 
 unsigned int NAU8810_BCLKDIV_4 ; 
 unsigned int NAU8810_BCLKDIV_8 ; 
 int /*<<< orphan*/  NAU8810_BCLKSEL_MASK ; 
 unsigned int NAU8810_CLKIO_MASTER ; 
 int /*<<< orphan*/  NAU8810_REG_CLOCK ; 
 int /*<<< orphan*/  NAU8810_REG_IFACE ; 
 int /*<<< orphan*/  NAU8810_REG_SMPLR ; 
 scalar_t__ NAU8810_SCLK_MCLK ; 
 int NAU8810_SMPLR_12K ; 
 int NAU8810_SMPLR_16K ; 
 int NAU8810_SMPLR_24K ; 
 int NAU8810_SMPLR_32K ; 
 int NAU8810_SMPLR_8K ; 
 int /*<<< orphan*/  NAU8810_SMPLR_MASK ; 
 int NAU8810_WLEN_20 ; 
 int NAU8810_WLEN_24 ; 
 int NAU8810_WLEN_32 ; 
 int /*<<< orphan*/  NAU8810_WLEN_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int nau8810_mclk_clkdiv (struct nau8810*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nau8810* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int nau8810_pcm_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct nau8810 *nau8810 = snd_soc_component_get_drvdata(component);
	int val_len = 0, val_rate = 0, ret = 0;
	unsigned int ctrl_val, bclk_fs, bclk_div;

	/* Select BCLK configuration if the codec as master. */
	regmap_read(nau8810->regmap, NAU8810_REG_CLOCK, &ctrl_val);
	if (ctrl_val & NAU8810_CLKIO_MASTER) {
		/* get the bclk and fs ratio */
		bclk_fs = snd_soc_params_to_bclk(params) / params_rate(params);
		if (bclk_fs <= 32)
			bclk_div = NAU8810_BCLKDIV_8;
		else if (bclk_fs <= 64)
			bclk_div = NAU8810_BCLKDIV_4;
		else if (bclk_fs <= 128)
			bclk_div = NAU8810_BCLKDIV_2;
		else
			return -EINVAL;
		regmap_update_bits(nau8810->regmap, NAU8810_REG_CLOCK,
			NAU8810_BCLKSEL_MASK, bclk_div);
	}

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		val_len |= NAU8810_WLEN_20;
		break;
	case 24:
		val_len |= NAU8810_WLEN_24;
		break;
	case 32:
		val_len |= NAU8810_WLEN_32;
		break;
	}

	switch (params_rate(params)) {
	case 8000:
		val_rate |= NAU8810_SMPLR_8K;
		break;
	case 11025:
		val_rate |= NAU8810_SMPLR_12K;
		break;
	case 16000:
		val_rate |= NAU8810_SMPLR_16K;
		break;
	case 22050:
		val_rate |= NAU8810_SMPLR_24K;
		break;
	case 32000:
		val_rate |= NAU8810_SMPLR_32K;
		break;
	case 44100:
	case 48000:
		break;
	}

	regmap_update_bits(nau8810->regmap, NAU8810_REG_IFACE,
		NAU8810_WLEN_MASK, val_len);
	regmap_update_bits(nau8810->regmap, NAU8810_REG_SMPLR,
		NAU8810_SMPLR_MASK, val_rate);

	/* If the master clock is from MCLK, provide the runtime FS for driver
	 * to get the master clock prescaler configuration.
	 */
	if (nau8810->clk_id == NAU8810_SCLK_MCLK) {
		ret = nau8810_mclk_clkdiv(nau8810, params_rate(params));
		if (ret < 0)
			dev_err(nau8810->dev, "MCLK div configuration fail\n");
	}

	return ret;
}