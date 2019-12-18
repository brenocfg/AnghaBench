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
struct adau1373_dai {int master; } ;
struct adau1373 {int /*<<< orphan*/  regmap; struct adau1373_dai* dais; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1373_DAI (size_t) ; 
 unsigned int ADAU1373_DAI_FORMAT_DSP ; 
 unsigned int ADAU1373_DAI_FORMAT_I2S ; 
 unsigned int ADAU1373_DAI_FORMAT_LEFT_J ; 
 unsigned int ADAU1373_DAI_FORMAT_RIGHT_J ; 
 unsigned int ADAU1373_DAI_INVERT_BCLK ; 
 unsigned int ADAU1373_DAI_INVERT_LRCLK ; 
 unsigned int ADAU1373_DAI_MASTER ; 
 int /*<<< orphan*/  ADAU1373_DAI_WLEN_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adau1373* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1373_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct adau1373 *adau1373 = snd_soc_component_get_drvdata(component);
	struct adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];
	unsigned int ctrl;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		ctrl = ADAU1373_DAI_MASTER;
		adau1373_dai->master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		ctrl = 0;
		adau1373_dai->master = false;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctrl |= ADAU1373_DAI_FORMAT_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		ctrl |= ADAU1373_DAI_FORMAT_LEFT_J;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		ctrl |= ADAU1373_DAI_FORMAT_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		ctrl |= ADAU1373_DAI_FORMAT_DSP;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		ctrl |= ADAU1373_DAI_INVERT_BCLK;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		ctrl |= ADAU1373_DAI_INVERT_LRCLK;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		ctrl |= ADAU1373_DAI_INVERT_LRCLK | ADAU1373_DAI_INVERT_BCLK;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(adau1373->regmap, ADAU1373_DAI(dai->id),
		~ADAU1373_DAI_WLEN_MASK, ctrl);

	return 0;
}