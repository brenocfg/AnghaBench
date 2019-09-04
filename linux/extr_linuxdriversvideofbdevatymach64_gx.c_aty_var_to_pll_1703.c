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
struct TYPE_2__ {int program_bits; short post_divider; int period_in_ps; scalar_t__ locationAddr; } ;
union aty_pll {TYPE_1__ ics2595; } ;
typedef  int u32 ;
typedef  int u16 ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int MAX_FREQ_2595 ; 
 int MIN_FREQ_2595 ; 
 int MIN_N_1703 ; 
 int REF_FREQ_2595 ; 

__attribute__((used)) static int aty_var_to_pll_1703(const struct fb_info *info, u32 vclk_per,
			       u32 bpp, union aty_pll *pll)
{
	u32 mhz100;		/* in 0.01 MHz */
	u32 program_bits;
	/* u32 post_divider; */
	u32 mach64MinFreq, mach64MaxFreq, mach64RefFreq;
	u32 temp, tempB;
	u16 remainder, preRemainder;
	short divider = 0, tempA;

	/* Calculate the programming word */
	mhz100 = 100000000 / vclk_per;
	mach64MinFreq = MIN_FREQ_2595;
	mach64MaxFreq = MAX_FREQ_2595;
	mach64RefFreq = REF_FREQ_2595;	/* 14.32 MHz */

	/* Calculate program word */
	if (mhz100 == 0)
		program_bits = 0xE0;
	else {
		if (mhz100 < mach64MinFreq)
			mhz100 = mach64MinFreq;
		if (mhz100 > mach64MaxFreq)
			mhz100 = mach64MaxFreq;

		divider = 0;
		while (mhz100 < (mach64MinFreq << 3)) {
			mhz100 <<= 1;
			divider += 0x20;
		}

		temp = (unsigned int) (mhz100);
		temp = (unsigned int) (temp * (MIN_N_1703 + 2));
		temp -= (short) (mach64RefFreq << 1);

		tempA = MIN_N_1703;
		preRemainder = 0xffff;

		do {
			tempB = temp;
			remainder = tempB % mach64RefFreq;
			tempB = tempB / mach64RefFreq;

			if ((tempB & 0xffff) <= 127
			    && (remainder <= preRemainder)) {
				preRemainder = remainder;
				divider &= ~0x1f;
				divider |= tempA;
				divider =
				    (divider & 0x00ff) +
				    ((tempB & 0xff) << 8);
			}

			temp += mhz100;
			tempA++;
		} while (tempA <= (MIN_N_1703 << 1));

		program_bits = divider;
	}

	pll->ics2595.program_bits = program_bits;
	pll->ics2595.locationAddr = 0;
	pll->ics2595.post_divider = divider;	/* fuer nix */
	pll->ics2595.period_in_ps = vclk_per;

	return 0;
}