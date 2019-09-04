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
 int /*<<< orphan*/  RT5651_PWR_ANLG2 ; 
 int /*<<< orphan*/  RT5651_PWR_BST1_OP2 ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5651_bst1_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST1_OP2, RT5651_PWR_BST1_OP2);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5651_PWR_ANLG2,
			RT5651_PWR_BST1_OP2, 0);
		break;

	default:
		return 0;
	}

	return 0;
}