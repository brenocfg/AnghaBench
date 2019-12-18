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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8962_ADC_DAC_CONTROL_1 ; 
 int /*<<< orphan*/  WM8962_ADC_VU ; 
 int /*<<< orphan*/  WM8962_DAC_MUTE ; 
 int /*<<< orphan*/  WM8962_LEFT_ADC_VOLUME ; 
 int /*<<< orphan*/  WM8962_RIGHT_ADC_VOLUME ; 
 int /*<<< orphan*/  WM8962_SOUNDSTAGE_ENABLES_0 ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8962_dsp2_set_enable(struct snd_soc_component *component, u16 val)
{
	u16 adcl = snd_soc_component_read32(component, WM8962_LEFT_ADC_VOLUME);
	u16 adcr = snd_soc_component_read32(component, WM8962_RIGHT_ADC_VOLUME);
	u16 dac = snd_soc_component_read32(component, WM8962_ADC_DAC_CONTROL_1);

	/* Mute the ADCs and DACs */
	snd_soc_component_write(component, WM8962_LEFT_ADC_VOLUME, 0);
	snd_soc_component_write(component, WM8962_RIGHT_ADC_VOLUME, WM8962_ADC_VU);
	snd_soc_component_update_bits(component, WM8962_ADC_DAC_CONTROL_1,
			    WM8962_DAC_MUTE, WM8962_DAC_MUTE);

	snd_soc_component_write(component, WM8962_SOUNDSTAGE_ENABLES_0, val);

	/* Restore the ADCs and DACs */
	snd_soc_component_write(component, WM8962_LEFT_ADC_VOLUME, adcl);
	snd_soc_component_write(component, WM8962_RIGHT_ADC_VOLUME, adcr);
	snd_soc_component_update_bits(component, WM8962_ADC_DAC_CONTROL_1,
			    WM8962_DAC_MUTE, dac);

	return 0;
}