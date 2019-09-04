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
struct adau1701 {unsigned int dai_fmt; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_SERICTL ; 
 unsigned int ADAU1701_SERICTL_INV_BCLK ; 
 unsigned int ADAU1701_SERICTL_INV_LRCLK ; 
 unsigned int ADAU1701_SERICTL_LEFTJ ; 
 unsigned int ADAU1701_SERICTL_RIGHTJ_24 ; 
 int /*<<< orphan*/  ADAU1701_SEROCTL ; 
 unsigned int ADAU1701_SEROCTL_INV_BCLK ; 
 unsigned int ADAU1701_SEROCTL_INV_LRCLK ; 
 unsigned int ADAU1701_SEROCTL_MASTER ; 
 unsigned int ADAU1701_SEROCTL_MSB_DEALY0 ; 
 unsigned int ADAU1701_SEROCTL_MSB_DEALY8 ; 
 unsigned int ADAU1701_SEROCTL_OBF16 ; 
 unsigned int ADAU1701_SEROCTL_OLF1024 ; 
 int /*<<< orphan*/  ADAU1701_SEROCTL_WORD_LEN_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
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
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1701_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	unsigned int serictl = 0x00, seroctl = 0x00;
	bool invert_lrclk;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		/* master, 64-bits per sample, 1 frame per sample */
		seroctl |= ADAU1701_SEROCTL_MASTER | ADAU1701_SEROCTL_OBF16
				| ADAU1701_SEROCTL_OLF1024;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		invert_lrclk = false;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		invert_lrclk = true;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		invert_lrclk = false;
		serictl |= ADAU1701_SERICTL_INV_BCLK;
		seroctl |= ADAU1701_SEROCTL_INV_BCLK;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		invert_lrclk = true;
		serictl |= ADAU1701_SERICTL_INV_BCLK;
		seroctl |= ADAU1701_SEROCTL_INV_BCLK;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		serictl |= ADAU1701_SERICTL_LEFTJ;
		seroctl |= ADAU1701_SEROCTL_MSB_DEALY0;
		invert_lrclk = !invert_lrclk;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		serictl |= ADAU1701_SERICTL_RIGHTJ_24;
		seroctl |= ADAU1701_SEROCTL_MSB_DEALY8;
		invert_lrclk = !invert_lrclk;
		break;
	default:
		return -EINVAL;
	}

	if (invert_lrclk) {
		seroctl |= ADAU1701_SEROCTL_INV_LRCLK;
		serictl |= ADAU1701_SERICTL_INV_LRCLK;
	}

	adau1701->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	regmap_write(adau1701->regmap, ADAU1701_SERICTL, serictl);
	regmap_update_bits(adau1701->regmap, ADAU1701_SEROCTL,
		~ADAU1701_SEROCTL_WORD_LEN_MASK, seroctl);

	return 0;
}