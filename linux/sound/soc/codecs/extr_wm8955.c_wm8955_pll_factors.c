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
struct pll_factors {int outdiv; unsigned int n; unsigned int k; } ;
struct device {int dummy; } ;

/* Variables and functions */
 long long FIXED_FLL_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int wm8955_pll_factors(struct device *dev,
			      int Fref, int Fout, struct pll_factors *pll)
{
	u64 Kpart;
	unsigned int K, Ndiv, Nmod, target;

	dev_dbg(dev, "Fref=%u Fout=%u\n", Fref, Fout);

	/* The oscilator should run at should be 90-100MHz, and
	 * there's a divide by 4 plus an optional divide by 2 in the
	 * output path to generate the system clock.  The clock table
	 * is sortd so we should always generate a suitable target. */
	target = Fout * 4;
	if (target < 90000000) {
		pll->outdiv = 1;
		target *= 2;
	} else {
		pll->outdiv = 0;
	}

	WARN_ON(target < 90000000 || target > 100000000);

	dev_dbg(dev, "Fvco=%dHz\n", target);

	/* Now, calculate N.K */
	Ndiv = target / Fref;

	pll->n = Ndiv;
	Nmod = target % Fref;
	dev_dbg(dev, "Nmod=%d\n", Nmod);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (long long)Nmod;

	do_div(Kpart, Fref);

	K = Kpart & 0xFFFFFFFF;

	if ((K % 10) >= 5)
		K += 5;

	/* Move down to proper range now rounding is done */
	pll->k = K / 10;

	dev_dbg(dev, "N=%x K=%x OUTDIV=%x\n", pll->n, pll->k, pll->outdiv);

	return 0;
}