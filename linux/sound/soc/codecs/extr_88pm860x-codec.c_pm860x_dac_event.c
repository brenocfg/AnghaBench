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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int DAC_LEFT ; 
 unsigned int DAC_MUTE ; 
 int DAC_RIGHT ; 
 unsigned int MODULATOR ; 
 int /*<<< orphan*/  PM860X_DAC_EN_2 ; 
 int /*<<< orphan*/  PM860X_DAC_OFFSET ; 
 int /*<<< orphan*/  PM860X_EAR_CTRL_2 ; 
 unsigned int RSYNC_CHANGE ; 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pm860x_dac_event(struct snd_soc_dapm_widget *w,
			    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int dac = 0;
	int data;

	if (!strcmp(w->name, "Left DAC"))
		dac = DAC_LEFT;
	if (!strcmp(w->name, "Right DAC"))
		dac = DAC_RIGHT;
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (dac) {
			/* Auto mute in power-on sequence. */
			dac |= MODULATOR;
			snd_soc_component_update_bits(component, PM860X_DAC_OFFSET,
					    DAC_MUTE, DAC_MUTE);
			snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
					    RSYNC_CHANGE, RSYNC_CHANGE);
			/* update dac */
			snd_soc_component_update_bits(component, PM860X_DAC_EN_2,
					    dac, dac);
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		if (dac) {
			/* Auto mute in power-off sequence. */
			snd_soc_component_update_bits(component, PM860X_DAC_OFFSET,
					    DAC_MUTE, DAC_MUTE);
			snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
					    RSYNC_CHANGE, RSYNC_CHANGE);
			/* update dac */
			data = snd_soc_component_read32(component, PM860X_DAC_EN_2);
			data &= ~dac;
			if (!(data & (DAC_LEFT | DAC_RIGHT)))
				data &= ~MODULATOR;
			snd_soc_component_write(component, PM860X_DAC_EN_2, data);
		}
		break;
	}
	return 0;
}