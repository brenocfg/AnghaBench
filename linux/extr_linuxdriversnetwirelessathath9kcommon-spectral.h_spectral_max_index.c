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
typedef  int s8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 spectral_max_index(u8 *bins, int num_bins)
{
	s8 m = (bins[2] & 0xfc) >> 2;
	u8 zero_idx = num_bins / 2;

	/* It's a 5 bit signed int, remove its sign and use one's
	 * complement interpretation to add the sign back to the 8
	 * bit int
	 */
	if (m & 0x20) {
		m &= ~0x20;
		m |= 0xe0;
	}

	/* Bring the zero point to the beginning
	 * instead of the middle so that we can use
	 * it for array lookup and that we don't deal
	 * with negative values later
	 */
	m += zero_idx;

	/* Sanity check to make sure index is within bounds */
	if (m < 0 || m > num_bins - 1)
		m = 0;

	return m;
}