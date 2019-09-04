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

__attribute__((used)) static inline unsigned find_last_zero_bit (unsigned char * bitmap,
	unsigned size, unsigned offset)
{
	unsigned bit, i;
	unsigned char * mapp;
	unsigned char map;

	mapp = bitmap + (size >> 3);
	map = *mapp--;
	bit = 1 << (size & 7);
	for (i = size; i > offset; i--) {
		if ((map & bit) == 0)
			break;
		if ((i & 7) != 0) {
			bit >>= 1;
		} else {
			map = *mapp--;
			bit = 1 << 7;
		}
	}
	return i;
}