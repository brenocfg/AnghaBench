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
struct max9867_priv {unsigned long pclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  master; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX9867_AUDIOCLKHIGH ; 
 int /*<<< orphan*/  MAX9867_AUDIOCLKLOW ; 
 int /*<<< orphan*/  MAX9867_IFC1B ; 
 int MAX9867_IFC1B_24BIT ; 
 int MAX9867_IFC1B_32BIT ; 
 int MAX9867_IFC1B_BCLK_MASK ; 
 int MAX9867_IFC1B_PCLK_16 ; 
 int MAX9867_IFC1B_PCLK_2 ; 
 int MAX9867_IFC1B_PCLK_4 ; 
 int MAX9867_IFC1B_PCLK_8 ; 
 int MAX9867_NI_HIGH_MASK ; 
 int MAX9867_NI_LOW_MASK ; 
 int MAX9867_PLL ; 
 int MAX9867_RAPID_LOCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_ni_value (int /*<<< orphan*/ ,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct max9867_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9867_dai_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	unsigned int ni_h, ni_l;
	int value;

	value = get_ni_value(max9867->sysclk, params_rate(params));
	if (value < 0)
		return value;

	ni_h = (0xFF00 & value) >> 8;
	ni_l = 0x00FF & value;
	/* set up the ni value */
	regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKHIGH,
		MAX9867_NI_HIGH_MASK, ni_h);
	regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKLOW,
		MAX9867_NI_LOW_MASK, ni_l);
	if (!max9867->master) {
		/*
		 * digital pll locks on to any externally supplied LRCLK signal
		 * and also enable rapid lock mode.
		 */
		regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKLOW,
			MAX9867_RAPID_LOCK, MAX9867_RAPID_LOCK);
		regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKHIGH,
			MAX9867_PLL, MAX9867_PLL);
	} else {
		unsigned long int bclk_rate, pclk_bclk_ratio;
		int bclk_value;

		bclk_rate = params_rate(params) * 2 * params_width(params);
		pclk_bclk_ratio = max9867->pclk/bclk_rate;
		switch (params_width(params)) {
		case 8:
		case 16:
			switch (pclk_bclk_ratio) {
			case 2:
				bclk_value = MAX9867_IFC1B_PCLK_2;
				break;
			case 4:
				bclk_value = MAX9867_IFC1B_PCLK_4;
				break;
			case 8:
				bclk_value = MAX9867_IFC1B_PCLK_8;
				break;
			case 16:
				bclk_value = MAX9867_IFC1B_PCLK_16;
				break;
			default:
				dev_err(component->dev,
					"unsupported sampling rate\n");
				return -EINVAL;
			}
			break;
		case 24:
			bclk_value = MAX9867_IFC1B_24BIT;
			break;
		case 32:
			bclk_value = MAX9867_IFC1B_32BIT;
			break;
		default:
			dev_err(component->dev, "unsupported sampling rate\n");
			return -EINVAL;
		}
		regmap_update_bits(max9867->regmap, MAX9867_IFC1B,
			MAX9867_IFC1B_BCLK_MASK, bclk_value);
	}
	return 0;
}