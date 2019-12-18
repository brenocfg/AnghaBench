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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGTL5000_CHIP_ANA_POWER ; 
 int /*<<< orphan*/  SGTL5000_VAG_POWERDOWN_DELAY ; 
 int SGTL5000_VAG_POWERUP ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vag_power_consumers (struct snd_soc_component*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vag_power_off(struct snd_soc_component *component, u32 source)
{
	u16 ana_pwr = snd_soc_component_read32(component,
					     SGTL5000_CHIP_ANA_POWER);

	if (!(ana_pwr & SGTL5000_VAG_POWERUP))
		return;

	/*
	 * This function calls when any of VAG power consumers is disappearing.
	 * Thus, if there is more than one consumer at the moment, as minimum
	 * one consumer will definitely stay after the end of the current
	 * event.
	 * Don't clear VAG_POWERUP if 2 or more consumers of VAG present:
	 * - LINE_IN (for HP events) / HP (for DAC/ADC events)
	 * - DAC
	 * - ADC
	 * (the current consumer is disappearing right now)
	 */
	if (vag_power_consumers(component, ana_pwr, source) >= 2)
		return;

	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
		SGTL5000_VAG_POWERUP, 0);
	/* In power down case, we need wait 400-1000 ms
	 * when VAG fully ramped down.
	 * As longer we wait, as smaller pop we've got.
	 */
	msleep(SGTL5000_VAG_POWERDOWN_DELAY);
}