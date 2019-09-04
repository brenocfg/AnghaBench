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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int WM8990_ALRCGPIO1 ; 
 int /*<<< orphan*/  WM8990_AUDIO_INTERFACE_4 ; 
 int /*<<< orphan*/  WM8990_GPIO1_GPIO2 ; 
 int WM8990_GPIO1_SEL_MASK ; 
 int /*<<< orphan*/  WM8990_LEFT_OUTPUT_VOLUME ; 
 int WM8990_OPCLK_ENA ; 
 int /*<<< orphan*/  WM8990_POWER_MANAGEMENT_2 ; 
 int /*<<< orphan*/  WM8990_RIGHT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8990_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8990_probe(struct snd_soc_component *component)
{
	wm8990_reset(component);

	/* charge output caps */
	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	snd_soc_component_update_bits(component, WM8990_AUDIO_INTERFACE_4,
			    WM8990_ALRCGPIO1, WM8990_ALRCGPIO1);

	snd_soc_component_update_bits(component, WM8990_GPIO1_GPIO2,
			    WM8990_GPIO1_SEL_MASK, 1);

	snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_2,
			    WM8990_OPCLK_ENA, WM8990_OPCLK_ENA);

	snd_soc_component_write(component, WM8990_LEFT_OUTPUT_VOLUME, 0x50 | (1<<8));
	snd_soc_component_write(component, WM8990_RIGHT_OUTPUT_VOLUME, 0x50 | (1<<8));

	return 0;
}