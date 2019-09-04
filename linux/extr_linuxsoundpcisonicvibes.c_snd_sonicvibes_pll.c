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
 int SV_ADCMULT ; 
 int SV_REFFREQUENCY ; 

__attribute__((used)) static void snd_sonicvibes_pll(unsigned int rate,
			       unsigned int *res_r,
			       unsigned int *res_m,
			       unsigned int *res_n)
{
	unsigned int r, m = 0, n = 0;
	unsigned int xm, xn, xr, xd, metric = ~0U;

	if (rate < 625000 / SV_ADCMULT)
		rate = 625000 / SV_ADCMULT;
	if (rate > 150000000 / SV_ADCMULT)
		rate = 150000000 / SV_ADCMULT;
	/* slight violation of specs, needed for continuous sampling rates */
	for (r = 0; rate < 75000000 / SV_ADCMULT; r += 0x20, rate <<= 1);
	for (xn = 3; xn < 33; xn++)	/* 35 */
		for (xm = 3; xm < 257; xm++) {
			xr = ((SV_REFFREQUENCY / SV_ADCMULT) * xm) / xn;
			if (xr >= rate)
				xd = xr - rate;
			else
				xd = rate - xr;
			if (xd < metric) {
				metric = xd;
				m = xm - 2;
				n = xn - 2;
			}
		}
	*res_r = r;
	*res_m = m;
	*res_n = n;
#if 0
	dev_dbg(sonic->card->dev,
		"metric = %i, xm = %i, xn = %i\n", metric, xm, xn);
	dev_dbg(sonic->card->dev,
		"pll: m = 0x%x, r = 0x%x, n = 0x%x\n", reg, m, r, n);
#endif
}