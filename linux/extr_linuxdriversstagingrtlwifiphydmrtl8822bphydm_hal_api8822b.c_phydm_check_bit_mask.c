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
typedef  int u8 ;
typedef  int u32 ;
typedef  int data_original ;

/* Variables and functions */

__attribute__((used)) static inline u32 phydm_check_bit_mask(u32 bit_mask, u32 data_original,
				       u32 data)
{
	u8 bit_shift;

	if (bit_mask != 0xfffff) {
		for (bit_shift = 0; bit_shift <= 19; bit_shift++) {
			if (((bit_mask >> bit_shift) & 0x1) == 1)
				break;
		}
		return ((data_original) & (~bit_mask)) | (data << bit_shift);
	}
	return data;
}