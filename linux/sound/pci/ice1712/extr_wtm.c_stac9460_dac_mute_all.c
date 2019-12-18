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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int STAC946X_LF_VOLUME ; 
 int STAC946X_MASTER_VOLUME ; 
 unsigned char stac9460_2_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stac9460_2_put (struct snd_ice1712*,int,unsigned char) ; 
 unsigned char stac9460_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stac9460_put (struct snd_ice1712*,int,unsigned char) ; 

__attribute__((used)) static void stac9460_dac_mute_all(struct snd_ice1712 *ice, unsigned char mute,
				unsigned short int *change_mask)
{
	unsigned char new, old;
	int id, idx, change;

	/*stac9460 1*/
	for (id = 0; id < 7; id++) {
		if (*change_mask & (0x01 << id)) {
			if (id == 0)
				idx = STAC946X_MASTER_VOLUME;
			else
				idx = STAC946X_LF_VOLUME - 1 + id;
			old = stac9460_get(ice, idx);
			new = (~mute << 7 & 0x80) | (old & ~0x80);
			change = (new != old);
			if (change) {
				stac9460_put(ice, idx, new);
				*change_mask = *change_mask | (0x01 << id);
			} else {
				*change_mask = *change_mask & ~(0x01 << id);
			}
		}
	}

	/*stac9460 2*/
	for (id = 0; id < 3; id++) {
		if (*change_mask & (0x01 << (id + 7))) {
			if (id == 0)
				idx = STAC946X_MASTER_VOLUME;
			else
				idx = STAC946X_LF_VOLUME - 1 + id;
			old = stac9460_2_get(ice, idx);
			new = (~mute << 7 & 0x80) | (old & ~0x80);
			change = (new != old);
			if (change) {
				stac9460_2_put(ice, idx, new);
				*change_mask = *change_mask | (0x01 << id);
			} else {
				*change_mask = *change_mask & ~(0x01 << id);
			}
		}
	}
}