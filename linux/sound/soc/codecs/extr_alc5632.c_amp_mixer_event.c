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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5632_HID_CTRL_DATA ; 
 int /*<<< orphan*/  ALC5632_HID_CTRL_INDEX ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amp_mixer_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	/* to power-on/off class-d amp generators/speaker */
	/* need to write to 'index-46h' register :        */
	/* so write index num (here 0x46) to reg 0x6a     */
	/* and then 0xffff/0 to reg 0x6c                  */
	snd_soc_component_write(component, ALC5632_HID_CTRL_INDEX, 0x46);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_write(component, ALC5632_HID_CTRL_DATA, 0xFFFF);
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_write(component, ALC5632_HID_CTRL_DATA, 0);
		break;
	}

	return 0;
}