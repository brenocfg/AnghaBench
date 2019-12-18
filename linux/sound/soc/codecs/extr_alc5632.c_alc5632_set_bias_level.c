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
 int ALC5632_PWR_ADD1_MAIN_BIAS ; 
 int ALC5632_PWR_ADD2_VREF ; 
 int /*<<< orphan*/  ALC5632_PWR_DOWN_CTRL_STATUS ; 
 int /*<<< orphan*/  ALC5632_PWR_DOWN_CTRL_STATUS_MASK ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD1 ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD1_MASK ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD2 ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD2_MASK ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD3 ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD3_MASK ; 
 int ALC5632_PWR_VREF_PR2 ; 
 int ALC5632_PWR_VREF_PR3 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  enable_power_depop (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alc5632_set_bias_level(struct snd_soc_component *component,
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
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_PWR_MANAG_ADD1_MASK,
				ALC5632_PWR_ADD1_MAIN_BIAS);
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_MANAG_ADD2_MASK,
				ALC5632_PWR_ADD2_VREF);
		/* "normal" mode: 0 @ 26 */
		snd_soc_component_update_bits(component, ALC5632_PWR_DOWN_CTRL_STATUS,
				ALC5632_PWR_DOWN_CTRL_STATUS_MASK,
				0xffff ^ (ALC5632_PWR_VREF_PR3
				| ALC5632_PWR_VREF_PR2));
		break;
	case SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_PWR_MANAG_ADD2_MASK, 0);
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD3,
				ALC5632_PWR_MANAG_ADD3_MASK, 0);
		snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_PWR_MANAG_ADD1_MASK, 0);
		break;
	}
	return 0;
}