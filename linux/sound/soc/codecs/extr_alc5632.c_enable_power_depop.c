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
 int /*<<< orphan*/  ALC5632_ADD1_POWER_EN ; 
 int /*<<< orphan*/  ALC5632_ADD2_POWER_EN ; 
 int /*<<< orphan*/  ALC5632_ADD3_POWER_EN ; 
 int /*<<< orphan*/  ALC5632_MISC_CTRL ; 
 int /*<<< orphan*/  ALC5632_MISC_HP_DEPOP_MODE2_EN ; 
 int /*<<< orphan*/  ALC5632_PWR_ADD1_SOFTGEN_EN ; 
 int /*<<< orphan*/  ALC5632_PWR_DOWN_CTRL_STATUS ; 
 int /*<<< orphan*/  ALC5632_PWR_DOWN_CTRL_STATUS_MASK ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD1 ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD2 ; 
 int /*<<< orphan*/  ALC5632_PWR_MANAG_ADD3 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_power_depop(struct snd_soc_component *component)
{
	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_PWR_ADD1_SOFTGEN_EN,
				ALC5632_PWR_ADD1_SOFTGEN_EN);

	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD3,
				ALC5632_ADD3_POWER_EN,
				ALC5632_ADD3_POWER_EN);

	snd_soc_component_update_bits(component, ALC5632_MISC_CTRL,
				ALC5632_MISC_HP_DEPOP_MODE2_EN,
				ALC5632_MISC_HP_DEPOP_MODE2_EN);

	/* "normal" mode: 0 @ 26 */
	/* set all PR0-7 mixers to 0 */
	snd_soc_component_update_bits(component, ALC5632_PWR_DOWN_CTRL_STATUS,
				ALC5632_PWR_DOWN_CTRL_STATUS_MASK,
				0);

	msleep(500);

	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD2,
				ALC5632_ADD2_POWER_EN,
				ALC5632_ADD2_POWER_EN);

	snd_soc_component_update_bits(component, ALC5632_PWR_MANAG_ADD1,
				ALC5632_ADD1_POWER_EN,
				ALC5632_ADD1_POWER_EN);

	/* disable HP Depop2 */
	snd_soc_component_update_bits(component, ALC5632_MISC_CTRL,
				ALC5632_MISC_HP_DEPOP_MODE2_EN,
				0);

}