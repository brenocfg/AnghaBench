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
struct madera_fll {int sync_src; unsigned int sync_freq; } ;

/* Variables and functions */
 int madera_apply_fll (struct madera_fll*) ; 

int madera_set_fll_syncclk(struct madera_fll *fll, int source,
			   unsigned int fref, unsigned int fout)
{
	/*
	 * fout is ignored, since the synchronizer is an optional extra
	 * constraint on the Fout generated from REFCLK, so the Fout is
	 * set when configuring REFCLK
	 */

	if (fll->sync_src == source && fll->sync_freq == fref)
		return 0;

	fll->sync_src = source;
	fll->sync_freq = fref;

	return madera_apply_fll(fll);
}