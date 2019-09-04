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
struct nau8825 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int NAU8825_HPL_VOL_MASK ; 
 unsigned int NAU8825_HPL_VOL_SFT ; 
 int NAU8825_HPR_VOL_MASK ; 
 unsigned int NAU8825_HP_VOL_MIN ; 
 int /*<<< orphan*/  NAU8825_REG_HSVOL_CTRL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void nau8825_hpvol_ramp(struct nau8825 *nau8825,
	unsigned int vol_from, unsigned int vol_to, unsigned int step)
{
	unsigned int value, volume, ramp_up, from, to;

	if (vol_from == vol_to || step == 0) {
		return;
	} else if (vol_from < vol_to) {
		ramp_up = true;
		from = vol_from;
		to = vol_to;
	} else {
		ramp_up = false;
		from = vol_to;
		to = vol_from;
	}
	/* only handle volume from 0dB to minimum -54dB */
	if (to > NAU8825_HP_VOL_MIN)
		to = NAU8825_HP_VOL_MIN;

	for (volume = from; volume < to; volume += step) {
		if (ramp_up)
			value = volume;
		else
			value = to - volume + from;
		regmap_update_bits(nau8825->regmap, NAU8825_REG_HSVOL_CTRL,
			NAU8825_HPL_VOL_MASK | NAU8825_HPR_VOL_MASK,
			(value << NAU8825_HPL_VOL_SFT) | value);
		usleep_range(10000, 10500);
	}
	if (ramp_up)
		value = to;
	else
		value = from;
	regmap_update_bits(nau8825->regmap, NAU8825_REG_HSVOL_CTRL,
		NAU8825_HPL_VOL_MASK | NAU8825_HPR_VOL_MASK,
		(value << NAU8825_HPL_VOL_SFT) | value);
}