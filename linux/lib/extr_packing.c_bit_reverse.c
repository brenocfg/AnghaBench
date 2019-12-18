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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 bit_reverse(u64 val, unsigned int width)
{
	u64 new_val = 0;
	unsigned int bit;
	unsigned int i;

	for (i = 0; i < width; i++) {
		bit = (val & (1 << i)) != 0;
		new_val |= (bit << (width - i - 1));
	}
	return new_val;
}