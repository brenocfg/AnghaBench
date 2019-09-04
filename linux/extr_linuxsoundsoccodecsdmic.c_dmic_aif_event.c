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
struct dmic {int /*<<< orphan*/  gpio_en; int /*<<< orphan*/  wakeup_delay; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct dmic* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmic_aif_event(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *kcontrol, int event) {
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct dmic *dmic = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (dmic->gpio_en)
			gpiod_set_value(dmic->gpio_en, 1);

		if (dmic->wakeup_delay)
			msleep(dmic->wakeup_delay);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (dmic->gpio_en)
			gpiod_set_value(dmic->gpio_en, 0);
		break;
	}

	return 0;
}