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
 int EINVAL ; 

__attribute__((used)) static int as3722_current_to_index(int min_uA, int max_uA,
		const int *curr_table, int n_currents)
{
	int i;

	for (i = n_currents - 1; i >= 0; i--) {
		if ((min_uA <= curr_table[i]) && (curr_table[i] <= max_uA))
			return i;
	}
	return -EINVAL;
}