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
struct wm_hubs_data {int /*<<< orphan*/  hp_startup_mode; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WM8993_ANALOGUE_HP_0 ; 
 int /*<<< orphan*/  WM8993_CHARGE_PUMP_1 ; 
 int WM8993_CP_ENA ; 
 int WM8993_HPOUT1L_DLY ; 
 int WM8993_HPOUT1L_ENA ; 
 int WM8993_HPOUT1R_DLY ; 
 int WM8993_HPOUT1R_ENA ; 
 int /*<<< orphan*/  WM8993_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_supply_event(struct snd_soc_dapm_widget *w,
			   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		switch (hubs->hp_startup_mode) {
		case 0:
			break;
		case 1:
			/* Enable the headphone amp */
			snd_soc_component_update_bits(component, WM8993_POWER_MANAGEMENT_1,
					    WM8993_HPOUT1L_ENA |
					    WM8993_HPOUT1R_ENA,
					    WM8993_HPOUT1L_ENA |
					    WM8993_HPOUT1R_ENA);

			/* Enable the second stage */
			snd_soc_component_update_bits(component, WM8993_ANALOGUE_HP_0,
					    WM8993_HPOUT1L_DLY |
					    WM8993_HPOUT1R_DLY,
					    WM8993_HPOUT1L_DLY |
					    WM8993_HPOUT1R_DLY);
			break;
		default:
			dev_err(component->dev, "Unknown HP startup mode %d\n",
				hubs->hp_startup_mode);
			break;
		}
		break;

	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8993_CHARGE_PUMP_1,
				    WM8993_CP_ENA, 0);
		break;
	}

	return 0;
}