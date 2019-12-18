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
struct max9867_priv {unsigned long pclk; int /*<<< orphan*/  regmap; scalar_t__ dsp_a; scalar_t__ master; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST_ULL (unsigned long long,unsigned long) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX9867_AUDIOCLKHIGH ; 
 int /*<<< orphan*/  MAX9867_AUDIOCLKLOW ; 
 int /*<<< orphan*/  MAX9867_IFC1B ; 
 int MAX9867_IFC1B_48X ; 
 int MAX9867_IFC1B_64X ; 
 int MAX9867_IFC1B_BCLK_MASK ; 
 int MAX9867_IFC1B_PCLK_16 ; 
 int MAX9867_IFC1B_PCLK_2 ; 
 int MAX9867_IFC1B_PCLK_4 ; 
 int MAX9867_IFC1B_PCLK_8 ; 
 int MAX9867_NI_HIGH_MASK ; 
 int MAX9867_NI_LOW_MASK ; 
 int MAX9867_PLL ; 
 int MAX9867_RAPID_LOCK ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct max9867_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9867_dai_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	int value;
	unsigned long int rate, ratio;
	struct snd_soc_component *component = dai->component;
	struct max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	unsigned int ni = DIV_ROUND_CLOSEST_ULL(96ULL * 0x10000 * params_rate(params),
						max9867->pclk);

	/* set up the ni value */
	regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKHIGH,
		MAX9867_NI_HIGH_MASK, (0xFF00 & ni) >> 8);
	regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKLOW,
		MAX9867_NI_LOW_MASK, 0x00FF & ni);
	if (max9867->master) {
		if (max9867->dsp_a) {
			value = MAX9867_IFC1B_48X;
		} else {
			rate = params_rate(params) * 2 * params_width(params);
			ratio = max9867->pclk / rate;
			switch (params_width(params)) {
			case 8:
			case 16:
				switch (ratio) {
				case 2:
					value = MAX9867_IFC1B_PCLK_2;
					break;
				case 4:
					value = MAX9867_IFC1B_PCLK_4;
					break;
				case 8:
					value = MAX9867_IFC1B_PCLK_8;
					break;
				case 16:
					value = MAX9867_IFC1B_PCLK_16;
					break;
				default:
					return -EINVAL;
				}
				break;
			case 24:
				value = MAX9867_IFC1B_48X;
				break;
			case 32:
				value = MAX9867_IFC1B_64X;
				break;
			default:
				return -EINVAL;
			}
		}
		regmap_update_bits(max9867->regmap, MAX9867_IFC1B,
			MAX9867_IFC1B_BCLK_MASK, value);
	} else {
		/*
		 * digital pll locks on to any externally supplied LRCLK signal
		 * and also enable rapid lock mode.
		 */
		regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKLOW,
			MAX9867_RAPID_LOCK, MAX9867_RAPID_LOCK);
		regmap_update_bits(max9867->regmap, MAX9867_AUDIOCLKHIGH,
			MAX9867_PLL, MAX9867_PLL);
	}
	return 0;
}