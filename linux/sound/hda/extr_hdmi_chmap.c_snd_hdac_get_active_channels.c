#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int channels; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* channel_allocations ; 
 int get_channel_allocation_order (int) ; 

int snd_hdac_get_active_channels(int ca)
{
	int ordered_ca = get_channel_allocation_order(ca);

	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	if (ordered_ca >= ARRAY_SIZE(channel_allocations))
		ordered_ca = 0;

	return channel_allocations[ordered_ca].channels;
}