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
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  TAS2552_CFG_1 ; 
 int /*<<< orphan*/  TAS2552_CFG_2 ; 
 int /*<<< orphan*/  TAS2552_LIMIT_RATE_HYS ; 
 int /*<<< orphan*/  TAS2552_RESERVED_0D ; 
 int TAS2552_SWS ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas2552_post_event(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_write(component, TAS2552_RESERVED_0D, 0xc0);
		snd_soc_component_update_bits(component, TAS2552_LIMIT_RATE_HYS, (1 << 5),
				    (1 << 5));
		snd_soc_component_update_bits(component, TAS2552_CFG_2, 1, 0);
		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_SWS, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_SWS,
				    TAS2552_SWS);
		snd_soc_component_update_bits(component, TAS2552_CFG_2, 1, 1);
		snd_soc_component_update_bits(component, TAS2552_LIMIT_RATE_HYS, (1 << 5), 0);
		snd_soc_component_write(component, TAS2552_RESERVED_0D, 0xbe);
		break;
	}
	return 0;
}