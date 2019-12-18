#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* speakers; } ;

/* Variables and functions */
 TYPE_1__* channel_allocations ; 
 int snd_hdac_spk_to_chmap (int) ; 

__attribute__((used)) static int from_cea_slot(int ordered_ca, unsigned char slot)
{
	int mask;

	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	if (slot >= 8)
		return 0;

	mask = channel_allocations[ordered_ca].speakers[7 - slot];

	return snd_hdac_spk_to_chmap(mask);
}