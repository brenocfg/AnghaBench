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
typedef  unsigned int u8 ;

/* Variables and functions */

__attribute__((used)) static int put_resource(u8 *rscs, unsigned int multi, unsigned int idx)
{
	unsigned int i, j, k, n;

	/* Mark the contiguous bits in resource bit-map as used */
	for (n = multi, i = idx; n > 0; n--) {
		j = i / 8;
		k = i % 8;
		rscs[j] &= ~((u8)1 << k);
		i++;
	}

	return 0;
}