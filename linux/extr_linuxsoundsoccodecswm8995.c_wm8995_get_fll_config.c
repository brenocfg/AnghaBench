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
typedef  int u64 ;
struct fll_div {int clk_ref_div; int outdiv; int fll_fratio; unsigned int n; unsigned int k; } ;

/* Variables and functions */
 int EINVAL ; 
 long long FIXED_FLL_SIZE ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static int wm8995_get_fll_config(struct fll_div *fll,
				 int freq_in, int freq_out)
{
	u64 Kpart;
	unsigned int K, Ndiv, Nmod;

	pr_debug("FLL input=%dHz, output=%dHz\n", freq_in, freq_out);

	/* Scale the input frequency down to <= 13.5MHz */
	fll->clk_ref_div = 0;
	while (freq_in > 13500000) {
		fll->clk_ref_div++;
		freq_in /= 2;

		if (fll->clk_ref_div > 3)
			return -EINVAL;
	}
	pr_debug("CLK_REF_DIV=%d, Fref=%dHz\n", fll->clk_ref_div, freq_in);

	/* Scale the output to give 90MHz<=Fvco<=100MHz */
	fll->outdiv = 3;
	while (freq_out * (fll->outdiv + 1) < 90000000) {
		fll->outdiv++;
		if (fll->outdiv > 63)
			return -EINVAL;
	}
	freq_out *= fll->outdiv + 1;
	pr_debug("OUTDIV=%d, Fvco=%dHz\n", fll->outdiv, freq_out);

	if (freq_in > 1000000) {
		fll->fll_fratio = 0;
	} else if (freq_in > 256000) {
		fll->fll_fratio = 1;
		freq_in *= 2;
	} else if (freq_in > 128000) {
		fll->fll_fratio = 2;
		freq_in *= 4;
	} else if (freq_in > 64000) {
		fll->fll_fratio = 3;
		freq_in *= 8;
	} else {
		fll->fll_fratio = 4;
		freq_in *= 16;
	}
	pr_debug("FLL_FRATIO=%d, Fref=%dHz\n", fll->fll_fratio, freq_in);

	/* Now, calculate N.K */
	Ndiv = freq_out / freq_in;

	fll->n = Ndiv;
	Nmod = freq_out % freq_in;
	pr_debug("Nmod=%d\n", Nmod);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (long long)Nmod;

	do_div(Kpart, freq_in);

	K = Kpart & 0xFFFFFFFF;

	if ((K % 10) >= 5)
		K += 5;

	/* Move down to proper range now rounding is done */
	fll->k = K / 10;

	pr_debug("N=%x K=%x\n", fll->n, fll->k);

	return 0;
}