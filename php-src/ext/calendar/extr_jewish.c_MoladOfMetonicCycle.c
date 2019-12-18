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
typedef  int zend_ulong ;
typedef  int zend_long ;

/* Variables and functions */
 int HALAKIM_PER_DAY ; 
 int HALAKIM_PER_METONIC_CYCLE ; 
 int NEW_MOON_OF_CREATION ; 

__attribute__((used)) static void MoladOfMetonicCycle(
								   int metonicCycle,
								   zend_long *pMoladDay,
								   zend_long *pMoladHalakim)
{
	register zend_ulong r1, r2, d1, d2;

	/* Start with the time of the first molad after creation. */
	r1 = NEW_MOON_OF_CREATION;

	/* Calculate metonicCycle * HALAKIM_PER_METONIC_CYCLE.  The upper 32
	 * bits of the result will be in r2 and the lower 16 bits will be
	 * in r1. */
	r1 += metonicCycle * (HALAKIM_PER_METONIC_CYCLE & 0xFFFF);
	r2 = r1 >> 16;
	r2 += metonicCycle * ((HALAKIM_PER_METONIC_CYCLE >> 16) & 0xFFFF);

	/* Calculate r2r1 / HALAKIM_PER_DAY.  The remainder will be in r1, the
	 * upper 16 bits of the quotient will be in d2 and the lower 16 bits
	 * will be in d1. */
	d2 = r2 / HALAKIM_PER_DAY;
	r2 -= d2 * HALAKIM_PER_DAY;
	r1 = (r2 << 16) | (r1 & 0xFFFF);
	d1 = r1 / HALAKIM_PER_DAY;
	r1 -= d1 * HALAKIM_PER_DAY;

	*pMoladDay = (d2 << 16) | d1;
	*pMoladHalakim = r1;
}