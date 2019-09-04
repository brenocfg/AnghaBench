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
 size_t USER_MAP ; 
 int** translations ; 

int conv_uni_to_8bit(u32 uni)
{
	int c;
	for (c = 0; c < 0x100; c++)
		if (translations[USER_MAP][c] == uni ||
		   (translations[USER_MAP][c] == (c | 0xf000) && uni == c))
			return c;
	return -1;
}