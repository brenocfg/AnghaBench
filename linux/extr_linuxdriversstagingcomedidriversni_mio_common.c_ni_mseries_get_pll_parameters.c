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
 unsigned int DIV_ROUND_CLOSEST (int,unsigned int const) ; 
 int EIO ; 
 unsigned int NI_M_PLL_MAX_DIVISOR ; 
 unsigned int NI_M_PLL_MAX_MULTIPLIER ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int ni_mseries_get_pll_parameters(unsigned int reference_period_ns,
					 unsigned int *freq_divider,
					 unsigned int *freq_multiplier,
					 unsigned int *actual_period_ns)
{
	unsigned int div;
	unsigned int best_div = 1;
	unsigned int mult;
	unsigned int best_mult = 1;
	static const unsigned int pico_per_nano = 1000;
	const unsigned int reference_picosec = reference_period_ns *
					       pico_per_nano;
	/*
	 * m-series wants the phased-locked loop to output 80MHz, which is
	 * divided by 4 to 20 MHz for most timing clocks
	 */
	static const unsigned int target_picosec = 12500;
	int best_period_picosec = 0;

	for (div = 1; div <= NI_M_PLL_MAX_DIVISOR; ++div) {
		for (mult = 1; mult <= NI_M_PLL_MAX_MULTIPLIER; ++mult) {
			unsigned int new_period_ps =
			    (reference_picosec * div) / mult;
			if (abs(new_period_ps - target_picosec) <
			    abs(best_period_picosec - target_picosec)) {
				best_period_picosec = new_period_ps;
				best_div = div;
				best_mult = mult;
			}
		}
	}
	if (best_period_picosec == 0)
		return -EIO;

	*freq_divider = best_div;
	*freq_multiplier = best_mult;
	/* return the actual period (* fudge factor for 80 to 20 MHz) */
	*actual_period_ns = DIV_ROUND_CLOSEST(best_period_picosec * 4,
					      pico_per_nano);
	return 0;
}