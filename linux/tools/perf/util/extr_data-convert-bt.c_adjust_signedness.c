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

__attribute__((used)) static unsigned long long adjust_signedness(unsigned long long value_int, int size)
{
	unsigned long long value_mask;

	/*
	 * value_mask = (1 << (size * 8 - 1)) - 1.
	 * Directly set value_mask for code readers.
	 */
	switch (size) {
	case 1:
		value_mask = 0x7fULL;
		break;
	case 2:
		value_mask = 0x7fffULL;
		break;
	case 4:
		value_mask = 0x7fffffffULL;
		break;
	case 8:
		/*
		 * For 64 bit value, return it self. There is no need
		 * to fill high bit.
		 */
		/* Fall through */
	default:
		/* BUG! */
		return value_int;
	}

	/* If it is a positive value, don't adjust. */
	if ((value_int & (~0ULL - value_mask)) == 0)
		return value_int;

	/* Fill upper part of value_int with 1 to make it a negative long long. */
	return (value_int & value_mask) | ~value_mask;
}