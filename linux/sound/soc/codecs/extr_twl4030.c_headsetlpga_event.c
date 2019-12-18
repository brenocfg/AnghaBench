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
struct twl4030_priv {int hsl_enabled; int /*<<< orphan*/  hsr_enabled; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  headset_ramp (struct snd_soc_component*,int) ; 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int headsetlpga_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* Do the ramp-up only once */
		if (!twl4030->hsr_enabled)
			headset_ramp(component, 1);

		twl4030->hsl_enabled = 1;
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* Do the ramp-down only if both headsetL/R is disabled */
		if (!twl4030->hsr_enabled)
			headset_ramp(component, 0);

		twl4030->hsl_enabled = 0;
		break;
	}
	return 0;
}