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
struct cs42l51_ratios {unsigned int ratio; int speed_mode; scalar_t__ mclk; } ;
struct cs42l51_private {int func; unsigned int mclk; int audio_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cs42l51_ratios*) ; 
 int CS42L51_DAC_DIF_I2S ; 
 int CS42L51_DAC_DIF_LJ24 ; 
 int CS42L51_DAC_DIF_RJ16 ; 
 int CS42L51_DAC_DIF_RJ18 ; 
 int CS42L51_DAC_DIF_RJ20 ; 
 int CS42L51_DAC_DIF_RJ24 ; 
 int CS42L51_DSM_MODE ; 
 int /*<<< orphan*/  CS42L51_INTF_CTL ; 
 int CS42L51_INTF_CTL_ADC_I2S ; 
 int CS42L51_INTF_CTL_DAC_FORMAT (int) ; 
 int CS42L51_INTF_CTL_MASTER ; 
 int /*<<< orphan*/  CS42L51_MIC_POWER_CTL ; 
 int CS42L51_MIC_POWER_CTL_AUTO ; 
 int CS42L51_MIC_POWER_CTL_MCLK_DIV2 ; 
 int CS42L51_MIC_POWER_CTL_SPEED (int) ; 
 int EINVAL ; 
#define  MODE_MASTER 133 
#define  MODE_SLAVE 132 
#define  MODE_SLAVE_AUTO 131 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cs42l51_ratios* master_ratios ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_width (struct snd_pcm_hw_params*) ; 
 struct cs42l51_ratios* slave_auto_ratios ; 
 struct cs42l51_ratios* slave_ratios ; 
 struct cs42l51_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs42l51_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs42l51_private *cs42l51 = snd_soc_component_get_drvdata(component);
	int ret;
	unsigned int i;
	unsigned int rate;
	unsigned int ratio;
	struct cs42l51_ratios *ratios = NULL;
	int nr_ratios = 0;
	int intf_ctl, power_ctl, fmt, mode;

	switch (cs42l51->func) {
	case MODE_MASTER:
		ratios = master_ratios;
		nr_ratios = ARRAY_SIZE(master_ratios);
		break;
	case MODE_SLAVE:
		ratios = slave_ratios;
		nr_ratios = ARRAY_SIZE(slave_ratios);
		break;
	case MODE_SLAVE_AUTO:
		ratios = slave_auto_ratios;
		nr_ratios = ARRAY_SIZE(slave_auto_ratios);
		break;
	}

	/* Figure out which MCLK/LRCK ratio to use */
	rate = params_rate(params);     /* Sampling rate, in Hz */
	ratio = cs42l51->mclk / rate;    /* MCLK/LRCK ratio */
	for (i = 0; i < nr_ratios; i++) {
		if (ratios[i].ratio == ratio)
			break;
	}

	if (i == nr_ratios) {
		/* We did not find a matching ratio */
		dev_err(component->dev, "could not find matching ratio\n");
		return -EINVAL;
	}

	intf_ctl = snd_soc_component_read32(component, CS42L51_INTF_CTL);
	power_ctl = snd_soc_component_read32(component, CS42L51_MIC_POWER_CTL);

	intf_ctl &= ~(CS42L51_INTF_CTL_MASTER | CS42L51_INTF_CTL_ADC_I2S
			| CS42L51_INTF_CTL_DAC_FORMAT(7));
	power_ctl &= ~(CS42L51_MIC_POWER_CTL_SPEED(3)
			| CS42L51_MIC_POWER_CTL_MCLK_DIV2);

	switch (cs42l51->func) {
	case MODE_MASTER:
		intf_ctl |= CS42L51_INTF_CTL_MASTER;
		mode = ratios[i].speed_mode;
		/* Force DSM mode if sampling rate is above 50kHz */
		if (rate > 50000)
			mode = CS42L51_DSM_MODE;
		power_ctl |= CS42L51_MIC_POWER_CTL_SPEED(mode);
		/*
		 * Auto detect mode is not applicable for master mode and has to
		 * be disabled. Otherwise SPEED[1:0] bits will be ignored.
		 */
		power_ctl &= ~CS42L51_MIC_POWER_CTL_AUTO;
		break;
	case MODE_SLAVE:
		power_ctl |= CS42L51_MIC_POWER_CTL_SPEED(ratios[i].speed_mode);
		break;
	case MODE_SLAVE_AUTO:
		power_ctl |= CS42L51_MIC_POWER_CTL_AUTO;
		break;
	}

	switch (cs42l51->audio_mode) {
	case SND_SOC_DAIFMT_I2S:
		intf_ctl |= CS42L51_INTF_CTL_ADC_I2S;
		intf_ctl |= CS42L51_INTF_CTL_DAC_FORMAT(CS42L51_DAC_DIF_I2S);
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		intf_ctl |= CS42L51_INTF_CTL_DAC_FORMAT(CS42L51_DAC_DIF_LJ24);
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		switch (params_width(params)) {
		case 16:
			fmt = CS42L51_DAC_DIF_RJ16;
			break;
		case 18:
			fmt = CS42L51_DAC_DIF_RJ18;
			break;
		case 20:
			fmt = CS42L51_DAC_DIF_RJ20;
			break;
		case 24:
			fmt = CS42L51_DAC_DIF_RJ24;
			break;
		default:
			dev_err(component->dev, "unknown format\n");
			return -EINVAL;
		}
		intf_ctl |= CS42L51_INTF_CTL_DAC_FORMAT(fmt);
		break;
	default:
		dev_err(component->dev, "unknown format\n");
		return -EINVAL;
	}

	if (ratios[i].mclk)
		power_ctl |= CS42L51_MIC_POWER_CTL_MCLK_DIV2;

	ret = snd_soc_component_write(component, CS42L51_INTF_CTL, intf_ctl);
	if (ret < 0)
		return ret;

	ret = snd_soc_component_write(component, CS42L51_MIC_POWER_CTL, power_ctl);
	if (ret < 0)
		return ret;

	return 0;
}