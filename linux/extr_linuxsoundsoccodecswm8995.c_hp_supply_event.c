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
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WM8995_ANALOGUE_HP_1 ; 
 int /*<<< orphan*/  WM8995_CHARGE_PUMP_1 ; 
 int WM8995_CP_ENA_MASK ; 
 int WM8995_HPOUT1L_DLY ; 
 int WM8995_HPOUT1L_DLY_MASK ; 
 int WM8995_HPOUT1L_ENA ; 
 int WM8995_HPOUT1L_ENA_MASK ; 
 int WM8995_HPOUT1R_DLY ; 
 int WM8995_HPOUT1R_DLY_MASK ; 
 int WM8995_HPOUT1R_ENA ; 
 int WM8995_HPOUT1R_ENA_MASK ; 
 int /*<<< orphan*/  WM8995_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_supply_event(struct snd_soc_dapm_widget *w,
			   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Enable the headphone amp */
		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_HPOUT1L_ENA_MASK |
				    WM8995_HPOUT1R_ENA_MASK,
				    WM8995_HPOUT1L_ENA |
				    WM8995_HPOUT1R_ENA);

		/* Enable the second stage */
		snd_soc_component_update_bits(component, WM8995_ANALOGUE_HP_1,
				    WM8995_HPOUT1L_DLY_MASK |
				    WM8995_HPOUT1R_DLY_MASK,
				    WM8995_HPOUT1L_DLY |
				    WM8995_HPOUT1R_DLY);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8995_CHARGE_PUMP_1,
				    WM8995_CP_ENA_MASK, 0);
		break;
	}

	return 0;
}