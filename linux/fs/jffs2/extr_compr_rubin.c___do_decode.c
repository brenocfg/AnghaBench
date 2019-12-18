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
struct rubin_state {unsigned long p; unsigned long q; int bit_number; unsigned long rec_q; int /*<<< orphan*/  pp; } ;

/* Variables and functions */
 unsigned long LOWER_BITS_RUBIN ; 
 unsigned long UPPER_BIT_RUBIN ; 
 int pullbit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __do_decode(struct rubin_state *rs, unsigned long p,
			unsigned long q)
{
	register unsigned long lower_bits_rubin = LOWER_BITS_RUBIN;
	unsigned long rec_q;
	int c, bits = 0;

	/*
	 * First, work out how many bits we need from the input stream.
	 * Note that we have already done the initial check on this
	 * loop prior to calling this function.
	 */
	do {
		bits++;
		q &= lower_bits_rubin;
		q <<= 1;
		p <<= 1;
	} while ((q >= UPPER_BIT_RUBIN) || ((p + q) <= UPPER_BIT_RUBIN));

	rs->p = p;
	rs->q = q;

	rs->bit_number += bits;

	/*
	 * Now get the bits.  We really want this to be "get n bits".
	 */
	rec_q = rs->rec_q;
	do {
		c = pullbit(&rs->pp);
		rec_q &= lower_bits_rubin;
		rec_q <<= 1;
		rec_q += c;
	} while (--bits);
	rs->rec_q = rec_q;
}