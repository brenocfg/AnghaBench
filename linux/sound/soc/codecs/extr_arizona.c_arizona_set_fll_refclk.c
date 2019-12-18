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
struct arizona_fll {int ref_src; unsigned int ref_freq; scalar_t__ fout; } ;

/* Variables and functions */
 int arizona_enable_fll (struct arizona_fll*) ; 
 int arizona_validate_fll (struct arizona_fll*,unsigned int,scalar_t__) ; 

int arizona_set_fll_refclk(struct arizona_fll *fll, int source,
			   unsigned int Fref, unsigned int Fout)
{
	int ret = 0;

	if (fll->ref_src == source && fll->ref_freq == Fref)
		return 0;

	if (fll->fout && Fref > 0) {
		ret = arizona_validate_fll(fll, Fref, fll->fout);
		if (ret != 0)
			return ret;
	}

	fll->ref_src = source;
	fll->ref_freq = Fref;

	if (fll->fout && Fref > 0)
		ret = arizona_enable_fll(fll);

	return ret;
}