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
typedef  int uint8 ;
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static uint8 *
createPaddedCopyWithLength(const uint8 *b, uint32 *l)
{
	uint8	   *ret;
	uint32		q;
	uint32		len,
				newLen448;
	uint32		len_high,
				len_low;		/* 64-bit value split into 32-bit sections */

	len = ((b == NULL) ? 0 : *l);
	newLen448 = len + 64 - (len % 64) - 8;
	if (newLen448 <= len)
		newLen448 += 64;

	*l = newLen448 + 8;
	if ((ret = (uint8 *) malloc(sizeof(uint8) * *l)) == NULL)
		return NULL;

	if (b != NULL)
		memcpy(ret, b, sizeof(uint8) * len);

	/* pad */
	ret[len] = 0x80;
	for (q = len + 1; q < newLen448; q++)
		ret[q] = 0x00;

	/* append length as a 64 bit bitcount */
	len_low = len;
	/* split into two 32-bit values */
	/* we only look at the bottom 32-bits */
	len_high = len >> 29;
	len_low <<= 3;
	q = newLen448;
	ret[q++] = (len_low & 0xff);
	len_low >>= 8;
	ret[q++] = (len_low & 0xff);
	len_low >>= 8;
	ret[q++] = (len_low & 0xff);
	len_low >>= 8;
	ret[q++] = (len_low & 0xff);
	ret[q++] = (len_high & 0xff);
	len_high >>= 8;
	ret[q++] = (len_high & 0xff);
	len_high >>= 8;
	ret[q++] = (len_high & 0xff);
	len_high >>= 8;
	ret[q] = (len_high & 0xff);

	return ret;
}