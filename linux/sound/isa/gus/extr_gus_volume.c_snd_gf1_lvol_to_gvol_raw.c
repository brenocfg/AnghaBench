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

/* Variables and functions */

unsigned short snd_gf1_lvol_to_gvol_raw(unsigned int vol)
{
	unsigned short e, m, tmp;

	if (vol > 65535)
		vol = 65535;
	tmp = vol;
	e = 7;
	if (tmp < 128) {
		while (e > 0 && tmp < (1 << e))
			e--;
	} else {
		while (tmp > 255) {
			tmp >>= 1;
			e++;
		}
	}
	m = vol - (1 << e);
	if (m > 0) {
		if (e > 8)
			m >>= e - 8;
		else if (e < 8)
			m <<= 8 - e;
		m &= 255;
	}
	return (e << 8) | m;
}