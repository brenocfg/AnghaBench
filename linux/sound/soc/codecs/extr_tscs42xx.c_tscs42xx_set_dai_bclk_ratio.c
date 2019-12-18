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
struct tscs42xx {unsigned int bclk_ratio; int /*<<< orphan*/  audio_params_lock; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RM_ADCSR_ABCM ; 
 int /*<<< orphan*/  RM_DACSR_DBCM ; 
 unsigned int RV_DACSR_DBCM_32 ; 
 unsigned int RV_DACSR_DBCM_40 ; 
 unsigned int RV_DACSR_DBCM_64 ; 
 int /*<<< orphan*/  R_ADCSR ; 
 int /*<<< orphan*/  R_DACSR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tscs42xx* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tscs42xx_set_dai_bclk_ratio(struct snd_soc_dai *codec_dai,
		unsigned int ratio)
{
	struct snd_soc_component *component = codec_dai->component;
	struct tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	unsigned int value;
	int ret = 0;

	switch (ratio) {
	case 32:
		value = RV_DACSR_DBCM_32;
		break;
	case 40:
		value = RV_DACSR_DBCM_40;
		break;
	case 64:
		value = RV_DACSR_DBCM_64;
		break;
	default:
		dev_err(component->dev, "Unsupported bclk ratio (%d)\n", ret);
		return -EINVAL;
	}

	ret = snd_soc_component_update_bits(component,
			R_DACSR, RM_DACSR_DBCM, value);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to set DAC BCLK ratio (%d)\n", ret);
		return ret;
	}
	ret = snd_soc_component_update_bits(component,
			R_ADCSR, RM_ADCSR_ABCM, value);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to set ADC BCLK ratio (%d)\n", ret);
		return ret;
	}

	mutex_lock(&tscs42xx->audio_params_lock);

	tscs42xx->bclk_ratio = ratio;

	mutex_unlock(&tscs42xx->audio_params_lock);

	return 0;
}