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
 unsigned char from_cea_slot (int,int) ; 
 int get_channel_allocation_order (int) ; 
 int** hdmi_channel_mapping ; 

__attribute__((used)) static void hdmi_setup_fake_chmap(unsigned char *map, int ca)
{
	int i;
	int ordered_ca = get_channel_allocation_order(ca);

	for (i = 0; i < 8; i++) {
		if (ordered_ca < ARRAY_SIZE(channel_allocations) &&
		    i < channel_allocations[ordered_ca].channels)
			map[i] = from_cea_slot(ordered_ca, hdmi_channel_mapping[ca][i] & 0x0f);
		else
			map[i] = 0;
	}
}