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
 int /*<<< orphan*/  ALC5623_PWR_ADD2_VREF ; 
 int /*<<< orphan*/  ALC5623_PWR_ADD3_MAIN_BIAS ; 
 int /*<<< orphan*/  ALC5623_PWR_MANAG_ADD1 ; 
 int /*<<< orphan*/  ALC5623_PWR_MANAG_ADD2 ; 
 int /*<<< orphan*/  ALC5623_PWR_MANAG_ADD3 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  enable_power_depop (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alc5623_set_bias_level(struct snd_soc_component *component,
				      enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_ON:
		enable_power_depop(component);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD2,
				ALC5623_PWR_ADD2_VREF);
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD3,
				ALC5623_PWR_ADD3_MAIN_BIAS);
		break;
	case SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD2, 0);
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD3, 0);
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD1, 0);
		break;
	}
	return 0;
}