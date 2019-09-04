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

__attribute__((used)) static inline int tda7419_vol_get_value(int val, unsigned int mask,
					int min, int thresh,
					unsigned int invert)
{
	val &= mask;
	if (val < thresh) {
		if (invert)
			val = 0 - val;
	} else if (val > thresh) {
		if (invert)
			val = val - thresh;
		else
			val = thresh - val;
	}

	if (val < min)
		val = min;

	return val;
}