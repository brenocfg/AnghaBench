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
typedef  int u32 ;
typedef  enum place_holder_in_cap_bitmap { ____Placeholder_place_holder_in_cap_bitmap } place_holder_in_cap_bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  wcn36xx_warn (char*,int) ; 

void set_feat_caps(u32 *bitmap, enum place_holder_in_cap_bitmap cap)
{
	int arr_idx, bit_idx;

	if (cap < 0 || cap > 127) {
		wcn36xx_warn("error cap idx %d\n", cap);
		return;
	}

	arr_idx = cap / 32;
	bit_idx = cap % 32;
	bitmap[arr_idx] |= (1 << bit_idx);
}