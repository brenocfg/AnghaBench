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
struct da7218_priv {scalar_t__ hp_single_supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7218_CP_CTRL ; 
 int /*<<< orphan*/  DA7218_CP_EN_MASK ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7218_cp_event(struct snd_soc_dapm_widget *w,
			   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	/*
	 * If this is DA7217 and we're using single supply for differential
	 * output, we really don't want to touch the charge pump.
	 */
	if (da7218->hp_single_supply)
		return 0;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, DA7218_CP_CTRL, DA7218_CP_EN_MASK,
				    DA7218_CP_EN_MASK);
		return 0;
	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, DA7218_CP_CTRL, DA7218_CP_EN_MASK,
				    0);
		return 0;
	default:
		return -EINVAL;
	}
}