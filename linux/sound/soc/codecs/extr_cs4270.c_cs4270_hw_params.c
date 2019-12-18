#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs4270_private {unsigned int mclk; int mode; scalar_t__ slave_mode; } ;
struct TYPE_2__ {unsigned int ratio; int mclk; int speed_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4270_FORMAT ; 
 int CS4270_FORMAT_ADC_I2S ; 
 int CS4270_FORMAT_ADC_LJ ; 
 int CS4270_FORMAT_ADC_MASK ; 
 int CS4270_FORMAT_DAC_I2S ; 
 int CS4270_FORMAT_DAC_LJ ; 
 int CS4270_FORMAT_DAC_MASK ; 
 int /*<<< orphan*/  CS4270_MODE ; 
 int CS4270_MODE_DIV_MASK ; 
 int CS4270_MODE_SLAVE ; 
 int CS4270_MODE_SPEED_MASK ; 
 int EINVAL ; 
 unsigned int NUM_MCLK_RATIOS ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 TYPE_1__* cs4270_mode_ratios ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct cs4270_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs4270_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs4270_private *cs4270 = snd_soc_component_get_drvdata(component);
	int ret;
	unsigned int i;
	unsigned int rate;
	unsigned int ratio;
	int reg;

	/* Figure out which MCLK/LRCK ratio to use */

	rate = params_rate(params);	/* Sampling rate, in Hz */
	ratio = cs4270->mclk / rate;	/* MCLK/LRCK ratio */

	for (i = 0; i < NUM_MCLK_RATIOS; i++) {
		if (cs4270_mode_ratios[i].ratio == ratio)
			break;
	}

	if (i == NUM_MCLK_RATIOS) {
		/* We did not find a matching ratio */
		dev_err(component->dev, "could not find matching ratio\n");
		return -EINVAL;
	}

	/* Set the sample rate */

	reg = snd_soc_component_read32(component, CS4270_MODE);
	reg &= ~(CS4270_MODE_SPEED_MASK | CS4270_MODE_DIV_MASK);
	reg |= cs4270_mode_ratios[i].mclk;

	if (cs4270->slave_mode)
		reg |= CS4270_MODE_SLAVE;
	else
		reg |= cs4270_mode_ratios[i].speed_mode;

	ret = snd_soc_component_write(component, CS4270_MODE, reg);
	if (ret < 0) {
		dev_err(component->dev, "i2c write failed\n");
		return ret;
	}

	/* Set the DAI format */

	reg = snd_soc_component_read32(component, CS4270_FORMAT);
	reg &= ~(CS4270_FORMAT_DAC_MASK | CS4270_FORMAT_ADC_MASK);

	switch (cs4270->mode) {
	case SND_SOC_DAIFMT_I2S:
		reg |= CS4270_FORMAT_DAC_I2S | CS4270_FORMAT_ADC_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg |= CS4270_FORMAT_DAC_LJ | CS4270_FORMAT_ADC_LJ;
		break;
	default:
		dev_err(component->dev, "unknown dai format\n");
		return -EINVAL;
	}

	ret = snd_soc_component_write(component, CS4270_FORMAT, reg);
	if (ret < 0) {
		dev_err(component->dev, "i2c write failed\n");
		return ret;
	}

	return ret;
}