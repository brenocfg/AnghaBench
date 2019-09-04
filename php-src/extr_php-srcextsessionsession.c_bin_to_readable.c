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
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hexconvtab ; 

__attribute__((used)) static void bin_to_readable(unsigned char *in, size_t inlen, char *out, size_t outlen, char nbits) /* {{{ */
{
	unsigned char *p, *q;
	unsigned short w;
	int mask;
	int have;

	p = (unsigned char *)in;
	q = (unsigned char *)in + inlen;

	w = 0;
	have = 0;
	mask = (1 << nbits) - 1;

	while (outlen--) {
		if (have < nbits) {
			if (p < q) {
				w |= *p++ << have;
				have += 8;
			} else {
				/* Should never happen. Input must be large enough. */
				ZEND_ASSERT(0);
				break;
			}
		}

		/* consume nbits */
		*out++ = hexconvtab[w & mask];
		w >>= nbits;
		have -= nbits;
	}

	*out = '\0';
}