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

__attribute__((used)) static unsigned int incbcd(unsigned int *bcd,
			   int inc,
			   unsigned char max,
			   size_t chars)
{
	unsigned int init = *bcd, i, j;
	unsigned long long c, dec = 0;

	/* If bcd is not in BCD format, just increment */
	if (max > 0x9) {
		*bcd += inc;
		return init;
	}

	/* Convert BCD to Decimal */
	for (i=0 ; i < chars ; i++) {
		c = (*bcd >> (i << 2)) & 0xf;
		c = c > 9 ? 9 : c; /* force to bcd just in case */
		for (j=0 ; j < i ; j++)
			c = c * 10;
		dec += c;
	}

	/* Do our increment/decrement */
	dec += inc;
	*bcd  = 0;

	/* Convert back to BCD */
	for (i=0 ; i < chars ; i++) {
		for (c=1,j=0 ; j < i ; j++)
			c = c * 10;
		c = (dec / c) % 10;
		*bcd += c << (i << 2);
	}
	return init;
}