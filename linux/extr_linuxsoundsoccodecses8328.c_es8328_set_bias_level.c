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
 int /*<<< orphan*/  ES8328_CHIPPOWER ; 
 int /*<<< orphan*/  ES8328_CONTROL1 ; 
 int ES8328_CONTROL1_ENREF ; 
 int ES8328_CONTROL1_VMIDSEL_500k ; 
 int ES8328_CONTROL1_VMIDSEL_50k ; 
 int ES8328_CONTROL1_VMIDSEL_5k ; 
 int ES8328_CONTROL1_VMIDSEL_MASK ; 
 int /*<<< orphan*/  ES8328_CONTROL2 ; 
 int ES8328_CONTROL2_OVERCURRENT_ON ; 
 int ES8328_CONTROL2_THERMAL_SHUTDOWN_ON ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int es8328_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VREF, VMID=2x50k, digital enabled */
		snd_soc_component_write(component, ES8328_CHIPPOWER, 0);
		snd_soc_component_update_bits(component, ES8328_CONTROL1,
				ES8328_CONTROL1_VMIDSEL_MASK |
				ES8328_CONTROL1_ENREF,
				ES8328_CONTROL1_VMIDSEL_50k |
				ES8328_CONTROL1_ENREF);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component, ES8328_CONTROL1,
					ES8328_CONTROL1_VMIDSEL_MASK |
					ES8328_CONTROL1_ENREF,
					ES8328_CONTROL1_VMIDSEL_5k |
					ES8328_CONTROL1_ENREF);

			/* Charge caps */
			msleep(100);
		}

		snd_soc_component_write(component, ES8328_CONTROL2,
				ES8328_CONTROL2_OVERCURRENT_ON |
				ES8328_CONTROL2_THERMAL_SHUTDOWN_ON);

		/* VREF, VMID=2*500k, digital stopped */
		snd_soc_component_update_bits(component, ES8328_CONTROL1,
				ES8328_CONTROL1_VMIDSEL_MASK |
				ES8328_CONTROL1_ENREF,
				ES8328_CONTROL1_VMIDSEL_500k |
				ES8328_CONTROL1_ENREF);
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, ES8328_CONTROL1,
				ES8328_CONTROL1_VMIDSEL_MASK |
				ES8328_CONTROL1_ENREF,
				0);
		break;
	}
	return 0;
}