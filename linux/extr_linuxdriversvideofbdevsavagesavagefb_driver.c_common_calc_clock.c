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
 long BASE_FREQ ; 
 long HALF_BASE_FREQ ; 

__attribute__((used)) static int common_calc_clock(long freq, int min_m, int min_n1, int max_n1,
			     int min_n2, int max_n2, long freq_min,
			     long freq_max, unsigned char *mdiv,
			     unsigned char *ndiv)
{
	long diff, best_diff;
	unsigned int m;
	unsigned char n1, n2;
	unsigned char best_n1 = 16+2, best_n2 = 2, best_m = 125+2;

	best_diff = freq;

	for (n2 = min_n2; n2 <= max_n2; n2++) {
		for (n1 = min_n1+2; n1 <= max_n1+2; n1++) {
			m = (freq * n1 * (1 << n2) + HALF_BASE_FREQ) /
				BASE_FREQ;
			if (m < min_m + 2 || m > 127+2)
				continue;
			if ((m * BASE_FREQ >= freq_min * n1) &&
			    (m * BASE_FREQ <= freq_max * n1)) {
				diff = freq * (1 << n2) * n1 - BASE_FREQ * m;
				if (diff < 0)
					diff = -diff;
				if (diff < best_diff) {
					best_diff = diff;
					best_m = m;
					best_n1 = n1;
					best_n2 = n2;
				}
			}
		}
	}

	if (max_n1 == 63)
		*ndiv = (best_n1 - 2) | (best_n2 << 6);
	else
		*ndiv = (best_n1 - 2) | (best_n2 << 5);

	*mdiv = best_m - 2;

	return 0;
}