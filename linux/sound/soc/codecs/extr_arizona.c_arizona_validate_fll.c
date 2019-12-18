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
struct arizona_fll {unsigned int fout; unsigned int vco_mult; } ;

/* Variables and functions */
 unsigned int ARIZONA_FLL_MAX_FREF ; 
 unsigned int ARIZONA_FLL_MAX_OUTDIV ; 
 unsigned int ARIZONA_FLL_MAX_REFDIV ; 
 unsigned int ARIZONA_FLL_MIN_FVCO ; 
 int EINVAL ; 
 int /*<<< orphan*/  arizona_fll_err (struct arizona_fll*,char*,...) ; 

__attribute__((used)) static int arizona_validate_fll(struct arizona_fll *fll,
				unsigned int Fref,
				unsigned int Fout)
{
	unsigned int Fvco_min;

	if (fll->fout && Fout != fll->fout) {
		arizona_fll_err(fll,
				"Can't change output on active FLL\n");
		return -EINVAL;
	}

	if (Fref / ARIZONA_FLL_MAX_REFDIV > ARIZONA_FLL_MAX_FREF) {
		arizona_fll_err(fll,
				"Can't scale %dMHz in to <=13.5MHz\n",
				Fref);
		return -EINVAL;
	}

	Fvco_min = ARIZONA_FLL_MIN_FVCO * fll->vco_mult;
	if (Fout * ARIZONA_FLL_MAX_OUTDIV < Fvco_min) {
		arizona_fll_err(fll, "No FLL_OUTDIV for Fout=%uHz\n",
				Fout);
		return -EINVAL;
	}

	return 0;
}