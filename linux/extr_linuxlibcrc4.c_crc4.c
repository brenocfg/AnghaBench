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
typedef  unsigned long long uint8_t ;
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 unsigned long long* crc4_tab ; 

uint8_t crc4(uint8_t c, uint64_t x, int bits)
{
	int i;

	/* mask off anything above the top bit */
	x &= (1ull << bits) - 1;

	/* Align to 4-bits */
	bits = (bits + 3) & ~0x3;

	/* Calculate crc4 over four-bit nibbles, starting at the MSbit */
	for (i = bits - 4; i >= 0; i -= 4)
		c = crc4_tab[c ^ ((x >> i) & 0xf)];

	return c;
}