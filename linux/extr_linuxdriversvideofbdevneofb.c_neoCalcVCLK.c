#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct neofb_par {int VCLK3NumeratorLow; int VCLK3NumeratorHigh; int VCLK3Denominator; } ;
struct TYPE_2__ {scalar_t__ accel; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 scalar_t__ FB_ACCEL_NEOMAGIC_NM2200 ; 
 scalar_t__ FB_ACCEL_NEOMAGIC_NM2230 ; 
 scalar_t__ FB_ACCEL_NEOMAGIC_NM2360 ; 
 scalar_t__ FB_ACCEL_NEOMAGIC_NM2380 ; 
 int MAX_D ; 
 int MAX_F ; 
 int MAX_N ; 
 long abs (long) ; 

__attribute__((used)) static void neoCalcVCLK(const struct fb_info *info,
			struct neofb_par *par, long freq)
{
	int n, d, f;
	int n_best = 0, d_best = 0, f_best = 0;
	long f_best_diff = 0x7ffff;

	for (f = 0; f <= MAX_F; f++)
		for (d = 0; d <= MAX_D; d++)
			for (n = 0; n <= MAX_N; n++) {
				long f_out;
				long f_diff;

				f_out = ((14318 * (n + 1)) / (d + 1)) >> f;
				f_diff = abs(f_out - freq);
				if (f_diff <= f_best_diff) {
					f_best_diff = f_diff;
					n_best = n;
					d_best = d;
					f_best = f;
				}
				if (f_out > freq)
					break;
			}

	if (info->fix.accel == FB_ACCEL_NEOMAGIC_NM2200 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2230 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2360 ||
	    info->fix.accel == FB_ACCEL_NEOMAGIC_NM2380) {
		/* NOT_DONE:  We are trying the full range of the 2200 clock.
		   We should be able to try n up to 2047 */
		par->VCLK3NumeratorLow = n_best;
		par->VCLK3NumeratorHigh = (f_best << 7);
	} else
		par->VCLK3NumeratorLow = n_best | (f_best << 7);

	par->VCLK3Denominator = d_best;

#ifdef NEOFB_DEBUG
	printk(KERN_DEBUG "neoVCLK: f:%ld NumLow=%d NumHi=%d Den=%d Df=%ld\n",
	       freq,
	       par->VCLK3NumeratorLow,
	       par->VCLK3NumeratorHigh,
	       par->VCLK3Denominator, f_best_diff);
#endif
}