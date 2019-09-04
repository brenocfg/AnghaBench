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

bool xt_find_jump_offset(const unsigned int *offsets,
			 unsigned int target, unsigned int size)
{
	int m, low = 0, hi = size;

	while (hi > low) {
		m = (low + hi) / 2u;

		if (offsets[m] > target)
			hi = m;
		else if (offsets[m] < target)
			low = m + 1;
		else
			return true;
	}

	return false;
}