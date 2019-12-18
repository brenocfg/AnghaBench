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
struct ubifs_info {int lpt_lebs; int main_lebs; int big_lpt; scalar_t__ lpt_sz; scalar_t__ leb_size; scalar_t__ ltab_sz; } ;

/* Variables and functions */
 int EINVAL ; 
 int UBIFS_MIN_LPT_LEBS ; 
 int div_u64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_calc_lpt_geom (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 

__attribute__((used)) static int calc_dflt_lpt_geom(struct ubifs_info *c, int *main_lebs,
			      int *big_lpt)
{
	int i, lebs_needed;
	long long sz;

	/* Start by assuming the minimum number of LPT LEBs */
	c->lpt_lebs = UBIFS_MIN_LPT_LEBS;
	c->main_lebs = *main_lebs - c->lpt_lebs;
	if (c->main_lebs <= 0)
		return -EINVAL;

	/* And assume we will use the small LPT model */
	c->big_lpt = 0;

	/*
	 * Calculate the geometry based on assumptions above and then see if it
	 * makes sense
	 */
	do_calc_lpt_geom(c);

	/* Small LPT model must have lpt_sz < leb_size */
	if (c->lpt_sz > c->leb_size) {
		/* Nope, so try again using big LPT model */
		c->big_lpt = 1;
		do_calc_lpt_geom(c);
	}

	/* Now check there are enough LPT LEBs */
	for (i = 0; i < 64 ; i++) {
		sz = c->lpt_sz * 4; /* Allow 4 times the size */
		lebs_needed = div_u64(sz + c->leb_size - 1, c->leb_size);
		if (lebs_needed > c->lpt_lebs) {
			/* Not enough LPT LEBs so try again with more */
			c->lpt_lebs = lebs_needed;
			c->main_lebs = *main_lebs - c->lpt_lebs;
			if (c->main_lebs <= 0)
				return -EINVAL;
			do_calc_lpt_geom(c);
			continue;
		}
		if (c->ltab_sz > c->leb_size) {
			ubifs_err(c, "LPT ltab too big");
			return -EINVAL;
		}
		*main_lebs = c->main_lebs;
		*big_lpt = c->big_lpt;
		return 0;
	}
	return -EINVAL;
}