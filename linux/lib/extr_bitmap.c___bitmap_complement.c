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
 unsigned int BITS_TO_LONGS (unsigned int) ; 

void __bitmap_complement(unsigned long *dst, const unsigned long *src, unsigned int bits)
{
	unsigned int k, lim = BITS_TO_LONGS(bits);
	for (k = 0; k < lim; ++k)
		dst[k] = ~src[k];
}