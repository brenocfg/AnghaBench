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

__attribute__((used)) static u32 ftdi_232bm_baud_base_to_divisor(int baud, int base)
{
	static const unsigned char divfrac[8] = { 0, 3, 2, 4, 1, 5, 6, 7 };
	u32 divisor;
	/* divisor shifted 3 bits to the left */
	int divisor3 = base / 2 / baud;
	divisor = divisor3 >> 3;
	divisor |= (u32)divfrac[divisor3 & 0x7] << 14;
	/* Deal with special cases for highest baud rates. */
	if (divisor == 1)
		divisor = 0;
	else if (divisor == 0x4001)
		divisor = 1;
	return divisor;
}