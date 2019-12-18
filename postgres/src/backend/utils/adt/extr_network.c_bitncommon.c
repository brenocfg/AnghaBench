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

int
bitncommon(const unsigned char *l, const unsigned char *r, int n)
{
	int			byte,
				nbits;

	/* number of bits to examine in last byte */
	nbits = n % 8;

	/* check whole bytes */
	for (byte = 0; byte < n / 8; byte++)
	{
		if (l[byte] != r[byte])
		{
			/* at least one bit in the last byte is not common */
			nbits = 7;
			break;
		}
	}

	/* check bits in last partial byte */
	if (nbits != 0)
	{
		/* calculate diff of first non-matching bytes */
		unsigned int diff = l[byte] ^ r[byte];

		/* compare the bits from the most to the least */
		while ((diff >> (8 - nbits)) != 0)
			nbits--;
	}

	return (8 * byte) + nbits;
}