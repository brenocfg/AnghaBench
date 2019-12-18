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
 int abs (int) ; 

__attribute__((used)) static inline int tda7419_vol_put_value(int val, int thresh,
					unsigned int invert)
{
	if (val < 0) {
		if (invert)
			val = abs(val);
		else
			val = thresh - val;
	} else if ((val > 0) && invert) {
		val += thresh;
	}

	return val;
}