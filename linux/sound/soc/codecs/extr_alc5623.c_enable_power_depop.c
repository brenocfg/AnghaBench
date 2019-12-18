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
struct alc5623_priv {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5623_ADD1_POWER_EN ; 
 int /*<<< orphan*/  ALC5623_ADD1_POWER_EN_5622 ; 
 int /*<<< orphan*/  ALC5623_ADD2_POWER_EN ; 
 int /*<<< orphan*/  ALC5623_ADD3_POWER_EN ; 
 int /*<<< orphan*/  ALC5623_MISC_CTRL ; 
 int /*<<< orphan*/  ALC5623_MISC_HP_DEPOP_MODE2_EN ; 
 int /*<<< orphan*/  ALC5623_PWR_ADD1_SOFTGEN_EN ; 
 int /*<<< orphan*/  ALC5623_PWR_MANAG_ADD1 ; 
 int /*<<< orphan*/  ALC5623_PWR_MANAG_ADD2 ; 
 int /*<<< orphan*/  ALC5623_PWR_MANAG_ADD3 ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct alc5623_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_power_depop(struct snd_soc_component *component)
{
	struct alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, ALC5623_PWR_MANAG_ADD1,
				ALC5623_PWR_ADD1_SOFTGEN_EN,
				ALC5623_PWR_ADD1_SOFTGEN_EN);

	snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD3, ALC5623_ADD3_POWER_EN);

	snd_soc_component_update_bits(component, ALC5623_MISC_CTRL,
				ALC5623_MISC_HP_DEPOP_MODE2_EN,
				ALC5623_MISC_HP_DEPOP_MODE2_EN);

	msleep(500);

	snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD2, ALC5623_ADD2_POWER_EN);

	/* avoid writing '1' into 5622 reserved bits */
	if (alc5623->id == 0x22)
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD1,
			ALC5623_ADD1_POWER_EN_5622);
	else
		snd_soc_component_write(component, ALC5623_PWR_MANAG_ADD1,
			ALC5623_ADD1_POWER_EN);

	/* disable HP Depop2 */
	snd_soc_component_update_bits(component, ALC5623_MISC_CTRL,
				ALC5623_MISC_HP_DEPOP_MODE2_EN,
				0);

}