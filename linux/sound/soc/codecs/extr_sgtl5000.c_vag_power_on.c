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
typedef  scalar_t__ u32 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 scalar_t__ HP_POWER_EVENT ; 
 int /*<<< orphan*/  SGTL5000_CHIP_ANA_POWER ; 
 scalar_t__ SGTL5000_HP_SEL_LINE_IN ; 
 int SGTL5000_VAG_POWERUP ; 
 int /*<<< orphan*/  SGTL5000_VAG_POWERUP_DELAY ; 
 scalar_t__ hp_sel_input (struct snd_soc_component*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vag_power_on(struct snd_soc_component *component, u32 source)
{
	if (snd_soc_component_read32(component, SGTL5000_CHIP_ANA_POWER) &
	    SGTL5000_VAG_POWERUP)
		return;

	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
			    SGTL5000_VAG_POWERUP, SGTL5000_VAG_POWERUP);

	/* When VAG powering on to get local loop from Line-In, the sleep
	 * is required to avoid loud pop.
	 */
	if (hp_sel_input(component) == SGTL5000_HP_SEL_LINE_IN &&
	    source == HP_POWER_EVENT)
		msleep(SGTL5000_VAG_POWERUP_DELAY);
}