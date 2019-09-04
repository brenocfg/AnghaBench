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
typedef  unsigned char u8 ;
typedef  int u32 ;

/* Variables and functions */

void netlbl_bitmap_setbit(unsigned char *bitmap, u32 bit, u8 state)
{
	u32 byte_spot;
	u8 bitmask;

	/* gcc always rounds to zero when doing integer division */
	byte_spot = bit / 8;
	bitmask = 0x80 >> (bit % 8);
	if (state)
		bitmap[byte_spot] |= bitmask;
	else
		bitmap[byte_spot] &= ~bitmask;
}