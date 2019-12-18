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
typedef  int u32 ;
typedef  int inbits ;

/* Variables and functions */
 unsigned long lcm (int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void krb5_nfold(u32 inbits, const u8 *in,
		       u32 outbits, u8 *out)
{
	unsigned long ulcm;
	int byte, i, msbit;

	/* the code below is more readable if I make these bytes
	   instead of bits */

	inbits >>= 3;
	outbits >>= 3;

	/* first compute lcm(n,k) */
	ulcm = lcm(inbits, outbits);

	/* now do the real work */

	memset(out, 0, outbits);
	byte = 0;

	/* this will end up cycling through k lcm(k,n)/k times, which
	   is correct */
	for (i = ulcm-1; i >= 0; i--) {
		/* compute the msbit in k which gets added into this byte */
		msbit = (
			/* first, start with the msbit in the first,
			 * unrotated byte */
			 ((inbits << 3) - 1)
			 /* then, for each byte, shift to the right
			  * for each repetition */
			 + (((inbits << 3) + 13) * (i/inbits))
			 /* last, pick out the correct byte within
			  * that shifted repetition */
			 + ((inbits - (i % inbits)) << 3)
			 ) % (inbits << 3);

		/* pull out the byte value itself */
		byte += (((in[((inbits - 1) - (msbit >> 3)) % inbits] << 8)|
				  (in[((inbits) - (msbit >> 3)) % inbits]))
				 >> ((msbit & 7) + 1)) & 0xff;

		/* do the addition */
		byte += out[i % outbits];
		out[i % outbits] = byte & 0xff;

		/* keep around the carry bit, if any */
		byte >>= 8;

	}

	/* if there's a carry bit left over, add it back in */
	if (byte) {
		for (i = outbits - 1; i >= 0; i--) {
			/* do the addition */
			byte += out[i];
			out[i] = byte & 0xff;

			/* keep around the carry bit, if any */
			byte >>= 8;
		}
	}
}