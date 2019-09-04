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

__attribute__((used)) static int atihdmi_paired_swap_fc_lfe(int pos)
{
	/*
	 * ATI/AMD have automatic FC/LFE swap built-in
	 * when in pairwise mapping mode.
	 */

	switch (pos) {
		/* see channel_allocations[].speakers[] */
		case 2: return 3;
		case 3: return 2;
		default: break;
	}

	return pos;
}