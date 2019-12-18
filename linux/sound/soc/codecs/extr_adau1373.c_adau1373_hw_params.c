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
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct adau1373_dai {unsigned int sysclk; int enable_src; } ;
struct adau1373 {int /*<<< orphan*/  regmap; struct adau1373_dai* dais; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1373_BCLKDIV (size_t) ; 
 unsigned int ADAU1373_BCLKDIV_64 ; 
 int ADAU1373_BCLKDIV_BCLK_MASK ; 
 int ADAU1373_BCLKDIV_SR_MASK ; 
 int /*<<< orphan*/  ADAU1373_DAI (size_t) ; 
 unsigned int ADAU1373_DAI_WLEN_16 ; 
 unsigned int ADAU1373_DAI_WLEN_20 ; 
 unsigned int ADAU1373_DAI_WLEN_24 ; 
 unsigned int ADAU1373_DAI_WLEN_32 ; 
 int ADAU1373_DAI_WLEN_MASK ; 
 int EINVAL ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct adau1373* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1373_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	struct adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];
	unsigned int div;
	unsigned int freq;
	unsigned int ctrl;

	freq = adau1373_dai->sysclk;

	if (freq % params_rate(params) != 0)
		return -EINVAL;

	switch (freq / params_rate(params)) {
	case 1024: /* sysclk / 256 */
		div = 0;
		break;
	case 1536: /* 2/3 sysclk / 256 */
		div = 1;
		break;
	case 2048: /* 1/2 sysclk / 256 */
		div = 2;
		break;
	case 3072: /* 1/3 sysclk / 256 */
		div = 3;
		break;
	case 4096: /* 1/4 sysclk / 256 */
		div = 4;
		break;
	case 6144: /* 1/6 sysclk / 256 */
		div = 5;
		break;
	case 5632: /* 2/11 sysclk / 256 */
		div = 6;
		break;
	default:
		return -EINVAL;
	}

	adau1373_dai->enable_src = (div != 0);

	regmap_update_bits(adau1373->regmap, ADAU1373_BCLKDIV(dai->id),
		ADAU1373_BCLKDIV_SR_MASK | ADAU1373_BCLKDIV_BCLK_MASK,
		(div << 2) | ADAU1373_BCLKDIV_64);

	switch (params_width(params)) {
	case 16:
		ctrl = ADAU1373_DAI_WLEN_16;
		break;
	case 20:
		ctrl = ADAU1373_DAI_WLEN_20;
		break;
	case 24:
		ctrl = ADAU1373_DAI_WLEN_24;
		break;
	case 32:
		ctrl = ADAU1373_DAI_WLEN_32;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(adau1373->regmap, ADAU1373_DAI(dai->id),
			ADAU1373_DAI_WLEN_MASK, ctrl);
}