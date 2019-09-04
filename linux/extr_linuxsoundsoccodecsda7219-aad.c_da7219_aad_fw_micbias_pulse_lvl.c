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
typedef  int u32 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7219_aad_micbias_pulse_lvl { ____Placeholder_da7219_aad_micbias_pulse_lvl } da7219_aad_micbias_pulse_lvl ;

/* Variables and functions */
 int DA7219_AAD_MICBIAS_PULSE_LVL_2_8V ; 
 int DA7219_AAD_MICBIAS_PULSE_LVL_2_9V ; 
 int DA7219_AAD_MICBIAS_PULSE_LVL_OFF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum da7219_aad_micbias_pulse_lvl
	da7219_aad_fw_micbias_pulse_lvl(struct snd_soc_component *component, u32 val)
{
	switch (val) {
	case 2800:
		return DA7219_AAD_MICBIAS_PULSE_LVL_2_8V;
	case 2900:
		return DA7219_AAD_MICBIAS_PULSE_LVL_2_9V;
	default:
		dev_warn(component->dev, "Invalid micbias pulse level");
		return DA7219_AAD_MICBIAS_PULSE_LVL_OFF;
	}
}