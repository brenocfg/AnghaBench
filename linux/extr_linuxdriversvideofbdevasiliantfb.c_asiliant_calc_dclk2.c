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
typedef  unsigned char u8 ;
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int Fref ; 

__attribute__((used)) static void asiliant_calc_dclk2(u32 *ppixclock, u8 *dclk2_m, u8 *dclk2_n, u8 *dclk2_div)
{
	unsigned pixclock = *ppixclock;
	unsigned Ftarget = 1000000 * (1000000 / pixclock);
	unsigned n;
	unsigned best_error = 0xffffffff;
	unsigned best_m = 0xffffffff,
	         best_n = 0xffffffff;
	unsigned ratio;
	unsigned remainder;
	unsigned char divisor = 0;

	/* Calculate the frequency required. This is hard enough. */
	ratio = 1000000 / pixclock;
	remainder = 1000000 % pixclock;
	Ftarget = 1000000 * ratio + (1000000 * remainder) / pixclock;

	while (Ftarget < 100000000) {
		divisor += 0x10;
		Ftarget <<= 1;
	}

	ratio = Ftarget / Fref;
	remainder = Ftarget % Fref;

	/* This expresses the constraint that 150kHz <= Fref/n <= 5Mhz,
	 * together with 3 <= n <= 257. */
	for (n = 3; n <= 257; n++) {
		unsigned m = n * ratio + (n * remainder) / Fref;

		/* 3 <= m <= 257 */
		if (m >= 3 && m <= 257) {
			unsigned new_error = Ftarget * n >= Fref * m ?
					       ((Ftarget * n) - (Fref * m)) : ((Fref * m) - (Ftarget * n));
			if (new_error < best_error) {
				best_n = n;
				best_m = m;
				best_error = new_error;
			}
		}
		/* But if VLD = 4, then 4m <= 1028 */
		else if (m <= 1028) {
			/* remember there are still only 8-bits of precision in m, so
			 * avoid over-optimistic error calculations */
			unsigned new_error = Ftarget * n >= Fref * (m & ~3) ?
					       ((Ftarget * n) - (Fref * (m & ~3))) : ((Fref * (m & ~3)) - (Ftarget * n));
			if (new_error < best_error) {
				best_n = n;
				best_m = m;
				best_error = new_error;
			}
		}
	}
	if (best_m > 257)
		best_m >>= 2;	/* divide m by 4, and leave VCO loop divide at 4 */
	else
		divisor |= 4;	/* or set VCO loop divide to 1 */
	*dclk2_m = best_m - 2;
	*dclk2_n = best_n - 2;
	*dclk2_div = divisor;
	*ppixclock = pixclock;
	return;
}