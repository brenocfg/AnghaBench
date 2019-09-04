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

/* Variables and functions */

__attribute__((used)) static unsigned short int ftdi_232am_baud_base_to_divisor(int baud, int base)
{
	unsigned short int divisor;
	/* divisor shifted 3 bits to the left */
	int divisor3 = base / 2 / baud;
	if ((divisor3 & 0x7) == 7)
		divisor3++; /* round x.7/8 up to x+1 */
	divisor = divisor3 >> 3;
	divisor3 &= 0x7;
	if (divisor3 == 1)
		divisor |= 0xc000;
	else if (divisor3 >= 4)
		divisor |= 0x4000;
	else if (divisor3 != 0)
		divisor |= 0x8000;
	else if (divisor == 1)
		divisor = 0;	/* special case for maximum baud rate */
	return divisor;
}