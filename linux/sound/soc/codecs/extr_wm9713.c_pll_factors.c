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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct _pll_div {int divsel; int divctl; int lf; unsigned int n; unsigned int k; } ;

/* Variables and functions */
 long long FIXED_PLL_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 

__attribute__((used)) static void pll_factors(struct snd_soc_component *component,
	struct _pll_div *pll_div, unsigned int source)
{
	u64 Kpart;
	unsigned int K, Ndiv, Nmod, target;

	/* The the PLL output is always 98.304MHz. */
	target = 98304000;

	/* If the input frequency is over 14.4MHz then scale it down. */
	if (source > 14400000) {
		source >>= 1;
		pll_div->divsel = 1;

		if (source > 14400000) {
			source >>= 1;
			pll_div->divctl = 1;
		} else
			pll_div->divctl = 0;

	} else {
		pll_div->divsel = 0;
		pll_div->divctl = 0;
	}

	/* Low frequency sources require an additional divide in the
	 * loop.
	 */
	if (source < 8192000) {
		pll_div->lf = 1;
		target >>= 2;
	} else
		pll_div->lf = 0;

	Ndiv = target / source;
	if ((Ndiv < 5) || (Ndiv > 12))
		dev_warn(component->dev,
			"WM9713 PLL N value %u out of recommended range!\n",
			Ndiv);

	pll_div->n = Ndiv;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (long long)Nmod;

	do_div(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check if we need to round */
	if ((K % 10) >= 5)
		K += 5;

	/* Move down to proper range now rounding is done */
	K /= 10;

	pll_div->k = K;
}