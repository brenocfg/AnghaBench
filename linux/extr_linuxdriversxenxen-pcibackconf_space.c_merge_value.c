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

__attribute__((used)) static inline u32 merge_value(u32 val, u32 new_val, u32 new_val_mask,
			      int offset)
{
	if (offset >= 0) {
		new_val_mask <<= (offset * 8);
		new_val <<= (offset * 8);
	} else {
		new_val_mask >>= (offset * -8);
		new_val >>= (offset * -8);
	}
	val = (val & ~new_val_mask) | (new_val & new_val_mask);

	return val;
}