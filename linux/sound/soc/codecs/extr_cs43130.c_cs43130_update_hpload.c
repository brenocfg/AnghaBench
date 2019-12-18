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
typedef  unsigned int u16 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs43130_private {unsigned int* hpload_dc; unsigned int** hpload_ac; int /*<<< orphan*/ * ac_freq; int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;

/* Variables and functions */
#define  CS43130_HPLOAD_AC_INT 129 
 unsigned int CS43130_HPLOAD_CHN_SEL ; 
#define  CS43130_HPLOAD_DC_INT 128 
 scalar_t__ CS43130_HP_AC_STAT_1 ; 
 scalar_t__ CS43130_HP_DC_STAT_1 ; 
 scalar_t__ CS43130_HP_LOAD_1 ; 
 size_t HP_LEFT ; 
 size_t HP_RIGHT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int cs43130_update_hpload(unsigned int msk, int ac_idx,
				 struct cs43130_private *cs43130)
{
	bool left_ch = true;
	unsigned int reg;
	u32 addr;
	u16 impedance;
	struct snd_soc_component *component = cs43130->component;

	switch (msk) {
	case CS43130_HPLOAD_DC_INT:
	case CS43130_HPLOAD_AC_INT:
		break;
	default:
		return 0;
	}

	regmap_read(cs43130->regmap, CS43130_HP_LOAD_1, &reg);
	if (reg & CS43130_HPLOAD_CHN_SEL)
		left_ch = false;

	if (msk == CS43130_HPLOAD_DC_INT)
		addr = CS43130_HP_DC_STAT_1;
	else
		addr = CS43130_HP_AC_STAT_1;

	regmap_read(cs43130->regmap, addr, &reg);
	impedance = reg >> 3;
	regmap_read(cs43130->regmap, addr + 1, &reg);
	impedance |= reg << 5;

	if (msk == CS43130_HPLOAD_DC_INT) {
		if (left_ch)
			cs43130->hpload_dc[HP_LEFT] = impedance;
		else
			cs43130->hpload_dc[HP_RIGHT] = impedance;

		dev_dbg(component->dev, "HP DC impedance (Ch %u): %u\n", !left_ch,
			impedance);
	} else {
		if (left_ch)
			cs43130->hpload_ac[ac_idx][HP_LEFT] = impedance;
		else
			cs43130->hpload_ac[ac_idx][HP_RIGHT] = impedance;

		dev_dbg(component->dev, "HP AC (%u Hz) impedance (Ch %u): %u\n",
			cs43130->ac_freq[ac_idx], !left_ch, impedance);
	}

	return 0;
}