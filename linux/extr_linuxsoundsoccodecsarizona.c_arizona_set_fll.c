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
struct arizona_fll {int sync_src; unsigned int sync_freq; unsigned int fout; scalar_t__ ref_src; unsigned int ref_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  arizona_disable_fll (struct arizona_fll*) ; 
 int arizona_enable_fll (struct arizona_fll*) ; 
 int arizona_validate_fll (struct arizona_fll*,unsigned int,unsigned int) ; 

int arizona_set_fll(struct arizona_fll *fll, int source,
		    unsigned int Fref, unsigned int Fout)
{
	int ret = 0;

	if (fll->sync_src == source &&
	    fll->sync_freq == Fref && fll->fout == Fout)
		return 0;

	if (Fout) {
		if (fll->ref_src >= 0) {
			ret = arizona_validate_fll(fll, fll->ref_freq, Fout);
			if (ret != 0)
				return ret;
		}

		ret = arizona_validate_fll(fll, Fref, Fout);
		if (ret != 0)
			return ret;
	}

	fll->sync_src = source;
	fll->sync_freq = Fref;
	fll->fout = Fout;

	if (Fout)
		ret = arizona_enable_fll(fll);
	else
		arizona_disable_fll(fll);

	return ret;
}