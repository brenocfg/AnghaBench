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
typedef  int u64 ;
struct wm8400_priv {TYPE_1__* wm8400; } ;
struct fll_factors {int outdiv; int freq_ref; int fratio; unsigned int n; unsigned int k; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 long long FIXED_FLL_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 

__attribute__((used)) static int fll_factors(struct wm8400_priv *wm8400, struct fll_factors *factors,
		       unsigned int Fref, unsigned int Fout)
{
	u64 Kpart;
	unsigned int K, Nmod, target;

	factors->outdiv = 2;
	while (Fout * factors->outdiv <  90000000 ||
	       Fout * factors->outdiv > 100000000) {
		factors->outdiv *= 2;
		if (factors->outdiv > 32) {
			dev_err(wm8400->wm8400->dev,
				"Unsupported FLL output frequency %uHz\n",
				Fout);
			return -EINVAL;
		}
	}
	target = Fout * factors->outdiv;
	factors->outdiv = factors->outdiv >> 2;

	if (Fref < 48000)
		factors->freq_ref = 1;
	else
		factors->freq_ref = 0;

	if (Fref < 1000000)
		factors->fratio = 9;
	else
		factors->fratio = 0;

	/* Ensure we have a fractional part */
	do {
		if (Fref < 1000000)
			factors->fratio--;
		else
			factors->fratio++;

		if (factors->fratio < 1 || factors->fratio > 8) {
			dev_err(wm8400->wm8400->dev,
				"Unable to calculate FRATIO\n");
			return -EINVAL;
		}

		factors->n = target / (Fref * factors->fratio);
		Nmod = target % (Fref * factors->fratio);
	} while (Nmod == 0);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (long long)Nmod;

	do_div(Kpart, (Fref * factors->fratio));

	K = Kpart & 0xFFFFFFFF;

	if ((K % 10) >= 5)
		K += 5;

	/* Move down to proper range now rounding is done */
	factors->k = K / 10;

	dev_dbg(wm8400->wm8400->dev,
		"FLL: Fref=%u Fout=%u N=%x K=%x, FRATIO=%x OUTDIV=%x\n",
		Fref, Fout,
		factors->n, factors->k, factors->fratio, factors->outdiv);

	return 0;
}