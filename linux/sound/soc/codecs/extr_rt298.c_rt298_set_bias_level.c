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
 int /*<<< orphan*/  AC_PWRST_D0 ; 
 int /*<<< orphan*/  AC_PWRST_D3 ; 
 int /*<<< orphan*/  RT298_SET_AUDIO_POWER ; 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  mdelay (int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt298_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (SND_SOC_BIAS_STANDBY ==
			snd_soc_component_get_bias_level(component)) {
			snd_soc_component_write(component,
				RT298_SET_AUDIO_POWER, AC_PWRST_D0);
			snd_soc_component_update_bits(component, 0x0d, 0x200, 0x200);
			snd_soc_component_update_bits(component, 0x52, 0x80, 0x0);
			mdelay(20);
			snd_soc_component_update_bits(component, 0x0d, 0x200, 0x0);
			snd_soc_component_update_bits(component, 0x52, 0x80, 0x80);
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_write(component,
			RT298_SET_AUDIO_POWER, AC_PWRST_D3);
		break;

	default:
		break;
	}

	return 0;
}