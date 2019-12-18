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
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int WM8961_ADCVU ; 
 int /*<<< orphan*/  WM8961_ADC_DAC_CONTROL_2 ; 
 int /*<<< orphan*/  WM8961_CHARGE_PUMP_B ; 
 int /*<<< orphan*/  WM8961_CLOCKING_3 ; 
 int WM8961_CP_DYN_PWR_MASK ; 
 int WM8961_DACSMM ; 
 int WM8961_IPVU ; 
 int WM8961_LO1ZC ; 
 int /*<<< orphan*/  WM8961_LOUT1_VOLUME ; 
 int /*<<< orphan*/  WM8961_LOUT2_VOLUME ; 
 int WM8961_MANUAL_MODE ; 
 int WM8961_OUT1VU ; 
 int /*<<< orphan*/  WM8961_RIGHT_ADC_VOLUME ; 
 int /*<<< orphan*/  WM8961_RIGHT_INPUT_VOLUME ; 
 int /*<<< orphan*/  WM8961_ROUT1_VOLUME ; 
 int /*<<< orphan*/  WM8961_ROUT2_VOLUME ; 
 int WM8961_SPKLZC ; 
 int WM8961_SPKRZC ; 
 int WM8961_SPKVU ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8961_probe(struct snd_soc_component *component)
{
	u16 reg;

	/* Enable class W */
	reg = snd_soc_component_read32(component, WM8961_CHARGE_PUMP_B);
	reg |= WM8961_CP_DYN_PWR_MASK;
	snd_soc_component_write(component, WM8961_CHARGE_PUMP_B, reg);

	/* Latch volume update bits (right channel only, we always
	 * write both out) and default ZC on. */
	reg = snd_soc_component_read32(component, WM8961_ROUT1_VOLUME);
	snd_soc_component_write(component, WM8961_ROUT1_VOLUME,
		     reg | WM8961_LO1ZC | WM8961_OUT1VU);
	snd_soc_component_write(component, WM8961_LOUT1_VOLUME, reg | WM8961_LO1ZC);
	reg = snd_soc_component_read32(component, WM8961_ROUT2_VOLUME);
	snd_soc_component_write(component, WM8961_ROUT2_VOLUME,
		     reg | WM8961_SPKRZC | WM8961_SPKVU);
	snd_soc_component_write(component, WM8961_LOUT2_VOLUME, reg | WM8961_SPKLZC);

	reg = snd_soc_component_read32(component, WM8961_RIGHT_ADC_VOLUME);
	snd_soc_component_write(component, WM8961_RIGHT_ADC_VOLUME, reg | WM8961_ADCVU);
	reg = snd_soc_component_read32(component, WM8961_RIGHT_INPUT_VOLUME);
	snd_soc_component_write(component, WM8961_RIGHT_INPUT_VOLUME, reg | WM8961_IPVU);

	/* Use soft mute by default */
	reg = snd_soc_component_read32(component, WM8961_ADC_DAC_CONTROL_2);
	reg |= WM8961_DACSMM;
	snd_soc_component_write(component, WM8961_ADC_DAC_CONTROL_2, reg);

	/* Use automatic clocking mode by default; for now this is all
	 * we support.
	 */
	reg = snd_soc_component_read32(component, WM8961_CLOCKING_3);
	reg &= ~WM8961_MANUAL_MODE;
	snd_soc_component_write(component, WM8961_CLOCKING_3, reg);

	return 0;
}