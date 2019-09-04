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

__attribute__((used)) static unsigned int calc_code_bit(unsigned int i, unsigned int *p_cache)
{
	unsigned int b, p = 0;

	/*
	 * Data bits are 0-based, but we're talking code bits, which
	 * are 1-based.
	 */
	b = i + 1;

	/* Use the cache if it is there */
	if (p_cache)
		p = *p_cache;
        b += p;

	/*
	 * For every power of two below our bit number, bump our bit.
	 *
	 * We compare with (b + 1) because we have to compare with what b
	 * would be _if_ it were bumped up by the parity bit.  Capice?
	 *
	 * p is set above.
	 */
	for (; (1 << p) < (b + 1); p++)
		b++;

	if (p_cache)
		*p_cache = p;

	return b;
}