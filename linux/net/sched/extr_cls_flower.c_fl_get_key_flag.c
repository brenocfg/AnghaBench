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

/* Variables and functions */

__attribute__((used)) static void fl_get_key_flag(u32 dissector_key, u32 dissector_mask,
			    u32 *flower_key, u32 *flower_mask,
			    u32 flower_flag_bit, u32 dissector_flag_bit)
{
	if (dissector_mask & dissector_flag_bit) {
		*flower_mask |= flower_flag_bit;
		if (dissector_key & dissector_flag_bit)
			*flower_key |= flower_flag_bit;
	}
}