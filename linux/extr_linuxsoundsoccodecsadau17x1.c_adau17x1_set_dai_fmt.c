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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct adau {int master; unsigned int dai_fmt; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_SERIAL_PORT0 ; 
 unsigned int ADAU17X1_SERIAL_PORT0_BCLK_POL ; 
 unsigned int ADAU17X1_SERIAL_PORT0_LRCLK_POL ; 
 unsigned int ADAU17X1_SERIAL_PORT0_MASTER ; 
 unsigned int ADAU17X1_SERIAL_PORT0_PULSE_MODE ; 
 int /*<<< orphan*/  ADAU17X1_SERIAL_PORT1 ; 
 unsigned int ADAU17X1_SERIAL_PORT1_DELAY0 ; 
 unsigned int ADAU17X1_SERIAL_PORT1_DELAY1 ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
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
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adau* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau17x1_set_dai_fmt(struct snd_soc_dai *dai,
		unsigned int fmt)
{
	struct adau *adau = snd_soc_component_get_drvdata(dai->component);
	unsigned int ctrl0, ctrl1;
	int lrclk_pol;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		ctrl0 = ADAU17X1_SERIAL_PORT0_MASTER;
		adau->master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		ctrl0 = 0;
		adau->master = false;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		lrclk_pol = 0;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY1;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		lrclk_pol = 1;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY0;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		lrclk_pol = 1;
		ctrl0 |= ADAU17X1_SERIAL_PORT0_PULSE_MODE;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY1;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		lrclk_pol = 1;
		ctrl0 |= ADAU17X1_SERIAL_PORT0_PULSE_MODE;
		ctrl1 = ADAU17X1_SERIAL_PORT1_DELAY0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		ctrl0 |= ADAU17X1_SERIAL_PORT0_BCLK_POL;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		lrclk_pol = !lrclk_pol;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		ctrl0 |= ADAU17X1_SERIAL_PORT0_BCLK_POL;
		lrclk_pol = !lrclk_pol;
		break;
	default:
		return -EINVAL;
	}

	if (lrclk_pol)
		ctrl0 |= ADAU17X1_SERIAL_PORT0_LRCLK_POL;

	regmap_write(adau->regmap, ADAU17X1_SERIAL_PORT0, ctrl0);
	regmap_write(adau->regmap, ADAU17X1_SERIAL_PORT1, ctrl1);

	adau->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	return 0;
}