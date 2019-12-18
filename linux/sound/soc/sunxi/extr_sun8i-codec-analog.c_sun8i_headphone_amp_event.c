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
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_OFF (int) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  SUN8I_ADDA_PAEN_HP_CTRL ; 
 int /*<<< orphan*/  SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_headphone_amp_event(struct snd_soc_dapm_widget *w,
				     struct snd_kcontrol *k, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		snd_soc_component_update_bits(component, SUN8I_ADDA_PAEN_HP_CTRL,
					      BIT(SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN),
					      BIT(SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN));
		/*
		 * Need a delay to have the amplifier up. 700ms seems the best
		 * compromise between the time to let the amplifier up and the
		 * time not to feel this delay while playing a sound.
		 */
		msleep(700);
	} else if (SND_SOC_DAPM_EVENT_OFF(event)) {
		snd_soc_component_update_bits(component, SUN8I_ADDA_PAEN_HP_CTRL,
					      BIT(SUN8I_ADDA_PAEN_HP_CTRL_HPPAEN),
					      0x0);
	}

	return 0;
}