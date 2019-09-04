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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8996_ACCESSORY_DETECT_MODE_1 ; 
 int /*<<< orphan*/  WM8996_ANALOGUE_HP_1 ; 
 int /*<<< orphan*/  WM8996_HEADPHONE_DETECT_1 ; 
 int WM8996_HPOUT1L_RMV_SHORT ; 
 int WM8996_HPOUT1R_RMV_SHORT ; 
 int WM8996_HP_POLL ; 
 int WM8996_JD_MODE_MASK ; 
 int WM8996_MICD_ENA ; 
 int /*<<< orphan*/  WM8996_MIC_DETECT_1 ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void wm8996_hpdet_start(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Unclamp the output, we can't measure while we're shorting it */
	snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_1,
			    WM8996_HPOUT1L_RMV_SHORT |
			    WM8996_HPOUT1R_RMV_SHORT,
			    WM8996_HPOUT1L_RMV_SHORT |
			    WM8996_HPOUT1R_RMV_SHORT);

	/* We need bandgap for HPDET */
	snd_soc_dapm_force_enable_pin(dapm, "Bandgap");
	snd_soc_dapm_sync(dapm);

	/* Go into headphone detect left mode */
	snd_soc_component_update_bits(component, WM8996_MIC_DETECT_1, WM8996_MICD_ENA, 0);
	snd_soc_component_update_bits(component, WM8996_ACCESSORY_DETECT_MODE_1,
			    WM8996_JD_MODE_MASK, 1);

	/* Trigger a measurement */
	snd_soc_component_update_bits(component, WM8996_HEADPHONE_DETECT_1,
			    WM8996_HP_POLL, WM8996_HP_POLL);
}