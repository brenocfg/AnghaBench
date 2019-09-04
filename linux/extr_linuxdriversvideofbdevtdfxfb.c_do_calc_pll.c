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
typedef  int u32 ;

/* Variables and functions */
 int abs (int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 

__attribute__((used)) static u32 do_calc_pll(int freq, int *freq_out)
{
	int m, n, k, best_m, best_n, best_k, best_error;
	int fref = 14318;

	best_error = freq;
	best_n = best_m = best_k = 0;

	for (k = 3; k >= 0; k--) {
		for (m = 63; m >= 0; m--) {
			/*
			 * Estimate value of n that produces target frequency
			 * with current m and k
			 */
			int n_estimated = ((freq * (m + 2) << k) / fref) - 2;

			/* Search neighborhood of estimated n */
			for (n = max(0, n_estimated);
				n <= min(255, n_estimated + 1);
				n++) {
				/*
				 * Calculate PLL freqency with current m, k and
				 * estimated n
				 */
				int f = (fref * (n + 2) / (m + 2)) >> k;
				int error = abs(f - freq);

				/*
				 * If this is the closest we've come to the
				 * target frequency then remember n, m and k
				 */
				if (error < best_error) {
					best_error = error;
					best_n = n;
					best_m = m;
					best_k = k;
				}
			}
		}
	}

	n = best_n;
	m = best_m;
	k = best_k;
	*freq_out = (fref * (n + 2) / (m + 2)) >> k;

	return (n << 8) | (m << 2) | k;
}