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
struct pll_timing {int p; int n; int m; } ;

/* Variables and functions */
 int DAC_FREF ; 
 int EINVAL ; 
 int VCO_MAX ; 
 int abs (int) ; 
 int /*<<< orphan*/  f_ddprintk (char*,int,int,int,int) ; 

__attribute__((used)) static int sst_calc_pll(const int freq, int *freq_out, struct pll_timing *t)
{
	int m, m2, n, p, best_err, fout;
	int best_n = -1;
	int best_m = -1;

	best_err = freq;
	p = 3;
	/* f * 2^P = vco should be less than VCOmax ~ 250 MHz for ics*/
	while (((1 << p) * freq > VCO_MAX) && (p >= 0))
		p--;
	if (p == -1)
		return -EINVAL;
	for (n = 1; n < 32; n++) {
		/* calc 2 * m so we can round it later*/
		m2 = (2 * freq * (1 << p) * (n + 2) ) / DAC_FREF - 4 ;

		m = (m2 % 2 ) ? m2/2+1 : m2/2 ;
		if (m >= 128)
			break;
		fout = (DAC_FREF * (m + 2)) / ((1 << p) * (n + 2));
		if ((abs(fout - freq) < best_err) && (m > 0)) {
			best_n = n;
			best_m = m;
			best_err = abs(fout - freq);
			/* we get the lowest m , allowing 0.5% error in freq*/
			if (200*best_err < freq) break;
		}
	}
	if (best_n == -1)  /* unlikely, but who knows ? */
		return -EINVAL;
	t->p = p;
	t->n = best_n;
	t->m = best_m;
	*freq_out = (DAC_FREF * (t->m + 2)) / ((1 << t->p) * (t->n + 2));
	f_ddprintk ("m: %d, n: %d, p: %d, F: %dKhz\n",
		  t->m, t->n, t->p, *freq_out);
	return 0;
}