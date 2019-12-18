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
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int dac33_hard_power (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  dac33_init_chip (struct snd_soc_component*) ; 
 int const snd_soc_component_get_bias_level (struct snd_soc_component*) ; 

__attribute__((used)) static int dac33_set_bias_level(struct snd_soc_component *component,
				enum snd_soc_bias_level level)
{
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			/* Coming from OFF, switch on the component */
			ret = dac33_hard_power(component, 1);
			if (ret != 0)
				return ret;

			dac33_init_chip(component);
		}
		break;
	case SND_SOC_BIAS_OFF:
		/* Do not power off, when the component is already off */
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			return 0;
		ret = dac33_hard_power(component, 0);
		if (ret != 0)
			return ret;
		break;
	}

	return 0;
}