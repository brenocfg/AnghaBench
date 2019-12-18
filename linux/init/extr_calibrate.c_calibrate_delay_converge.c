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
 unsigned long LPS_PREC ; 
 int /*<<< orphan*/  __delay (unsigned long) ; 
 unsigned long jiffies ; 

__attribute__((used)) static unsigned long calibrate_delay_converge(void)
{
	/* First stage - slowly accelerate to find initial bounds */
	unsigned long lpj, lpj_base, ticks, loopadd, loopadd_base, chop_limit;
	int trials = 0, band = 0, trial_in_band = 0;

	lpj = (1<<12);

	/* wait for "start of" clock tick */
	ticks = jiffies;
	while (ticks == jiffies)
		; /* nothing */
	/* Go .. */
	ticks = jiffies;
	do {
		if (++trial_in_band == (1<<band)) {
			++band;
			trial_in_band = 0;
		}
		__delay(lpj * band);
		trials += band;
	} while (ticks == jiffies);
	/*
	 * We overshot, so retreat to a clear underestimate. Then estimate
	 * the largest likely undershoot. This defines our chop bounds.
	 */
	trials -= band;
	loopadd_base = lpj * band;
	lpj_base = lpj * trials;

recalibrate:
	lpj = lpj_base;
	loopadd = loopadd_base;

	/*
	 * Do a binary approximation to get lpj set to
	 * equal one clock (up to LPS_PREC bits)
	 */
	chop_limit = lpj >> LPS_PREC;
	while (loopadd > chop_limit) {
		lpj += loopadd;
		ticks = jiffies;
		while (ticks == jiffies)
			; /* nothing */
		ticks = jiffies;
		__delay(lpj);
		if (jiffies != ticks)	/* longer than 1 tick */
			lpj -= loopadd;
		loopadd >>= 1;
	}
	/*
	 * If we incremented every single time possible, presume we've
	 * massively underestimated initially, and retry with a higher
	 * start, and larger range. (Only seen on x86_64, due to SMIs)
	 */
	if (lpj + loopadd * 2 == lpj_base + loopadd_base * 2) {
		lpj_base = lpj;
		loopadd_base <<= 2;
		goto recalibrate;
	}

	return lpj;
}