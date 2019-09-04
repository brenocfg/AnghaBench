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
 int /*<<< orphan*/  AC97_EXTENDED_MID ; 
 int /*<<< orphan*/  AC97_EXTENDED_MSTATUS ; 
 int /*<<< orphan*/  AC97_POWERDOWN ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9713_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_ON:
		/* enable thermal shutdown */
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0xe400, 0x0000);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* enable master bias and vmid */
		snd_soc_component_update_bits(component, AC97_EXTENDED_MID, 0xc400, 0x0000);
		snd_soc_component_write(component, AC97_POWERDOWN, 0x0000);
		break;
	case SND_SOC_BIAS_OFF:
		/* disable everything including AC link */
		snd_soc_component_write(component, AC97_EXTENDED_MID, 0xffff);
		snd_soc_component_write(component, AC97_EXTENDED_MSTATUS, 0xffff);
		snd_soc_component_write(component, AC97_POWERDOWN, 0xffff);
		break;
	}
	return 0;
}