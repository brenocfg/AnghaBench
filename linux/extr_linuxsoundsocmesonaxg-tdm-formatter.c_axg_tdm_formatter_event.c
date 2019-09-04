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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct axg_tdm_formatter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  axg_tdm_formatter_power_down (struct axg_tdm_formatter*) ; 
 int axg_tdm_formatter_power_up (struct axg_tdm_formatter*,struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct axg_tdm_formatter* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int axg_tdm_formatter_event(struct snd_soc_dapm_widget *w,
			    struct snd_kcontrol *control,
			    int event)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct axg_tdm_formatter *formatter = snd_soc_component_get_drvdata(c);
	int ret = 0;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		ret = axg_tdm_formatter_power_up(formatter, w);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		axg_tdm_formatter_power_down(formatter);
		break;

	default:
		dev_err(c->dev, "Unexpected event %d\n", event);
		return -EINVAL;
	}

	return ret;
}