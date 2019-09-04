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
struct ssm4567 {int dummy; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct ssm4567* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int ssm4567_set_power (struct ssm4567*,int) ; 

__attribute__((used)) static int ssm4567_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct ssm4567 *ssm4567 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			ret = ssm4567_set_power(ssm4567, true);
		break;
	case SND_SOC_BIAS_OFF:
		ret = ssm4567_set_power(ssm4567, false);
		break;
	}

	return ret;
}