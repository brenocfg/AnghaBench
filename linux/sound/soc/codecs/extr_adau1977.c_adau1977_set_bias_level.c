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
struct snd_soc_component {int dummy; } ;
struct adau1977 {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int adau1977_power_disable (struct adau1977*) ; 
 int adau1977_power_enable (struct adau1977*) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct adau1977* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1977_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			ret = adau1977_power_enable(adau1977);
		break;
	case SND_SOC_BIAS_OFF:
		ret = adau1977_power_disable(adau1977);
		break;
	}

	return ret;
}