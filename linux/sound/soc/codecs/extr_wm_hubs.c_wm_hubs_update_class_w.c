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
struct wm_hubs_data {int /*<<< orphan*/  (* check_class_w_digital ) (struct snd_soc_component*) ;} ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8993_CLASS_W_0 ; 
 int WM8993_CP_DYN_FREQ ; 
 int WM8993_CP_DYN_V ; 
 int /*<<< orphan*/  WM8993_LEFT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  WM8993_RIGHT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,char*) ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm_hubs_dac_hp_direct (struct snd_soc_component*) ; 

void wm_hubs_update_class_w(struct snd_soc_component *component)
{
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	int enable = WM8993_CP_DYN_V | WM8993_CP_DYN_FREQ;

	if (!wm_hubs_dac_hp_direct(component))
		enable = false;

	if (hubs->check_class_w_digital && !hubs->check_class_w_digital(component))
		enable = false;

	dev_vdbg(component->dev, "Class W %s\n", enable ? "enabled" : "disabled");

	snd_soc_component_update_bits(component, WM8993_CLASS_W_0,
			    WM8993_CP_DYN_V | WM8993_CP_DYN_FREQ, enable);

	snd_soc_component_write(component, WM8993_LEFT_OUTPUT_VOLUME,
		      snd_soc_component_read32(component, WM8993_LEFT_OUTPUT_VOLUME));
	snd_soc_component_write(component, WM8993_RIGHT_OUTPUT_VOLUME,
		      snd_soc_component_read32(component, WM8993_RIGHT_OUTPUT_VOLUME));
}