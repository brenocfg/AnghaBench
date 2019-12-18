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
struct da7219_priv {int /*<<< orphan*/  gain_ramp_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_GAIN_RAMP_CTRL ; 
 int /*<<< orphan*/  DA7219_GAIN_RAMP_RATE_NOMINAL ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7219_gain_ramp_event(struct snd_soc_dapm_widget *w,
				  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
	case SND_SOC_DAPM_PRE_PMD:
		/* Ensure nominal gain ramping for DAPM sequence */
		da7219->gain_ramp_ctrl =
			snd_soc_component_read32(component, DA7219_GAIN_RAMP_CTRL);
		snd_soc_component_write(component, DA7219_GAIN_RAMP_CTRL,
			      DA7219_GAIN_RAMP_RATE_NOMINAL);
		break;
	case SND_SOC_DAPM_POST_PMU:
	case SND_SOC_DAPM_POST_PMD:
		/* Restore previous gain ramp settings */
		snd_soc_component_write(component, DA7219_GAIN_RAMP_CTRL,
			      da7219->gain_ramp_ctrl);
		break;
	}

	return 0;
}