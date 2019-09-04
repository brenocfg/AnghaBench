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

/* Variables and functions */
 int** db_invert_table ; 

u32 odm_convert_to_linear(u32 value)
{
	u8 i;
	u8 j;
	u32 linear;

	/* 1dB~96dB */

	value = value & 0xFF;

	i = (u8)((value - 1) >> 3);
	j = (u8)(value - 1) - (i << 3);

	linear = db_invert_table[i][j];

	return linear;
}