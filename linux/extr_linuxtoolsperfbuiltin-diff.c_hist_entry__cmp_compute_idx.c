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
struct hist_entry {scalar_t__ dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int COMPUTE_DELTA ; 
 int COMPUTE_DELTA_ABS ; 
 int __hist_entry__cmp_compute (struct hist_entry*,struct hist_entry*,int) ; 
 int /*<<< orphan*/ * data__files ; 
 struct hist_entry* get_pair_data (struct hist_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
hist_entry__cmp_compute_idx(struct hist_entry *left, struct hist_entry *right,
			    int c, int sort_idx)
{
	struct hist_entry *p_right, *p_left;

	p_left  = get_pair_data(left,  &data__files[sort_idx]);
	p_right = get_pair_data(right, &data__files[sort_idx]);

	if (!p_left && !p_right)
		return 0;

	if (!p_left || !p_right)
		return p_left ? -1 : 1;

	if (c != COMPUTE_DELTA && c != COMPUTE_DELTA_ABS) {
		/*
		 * The delta can be computed without the baseline, but
		 * others are not.  Put those entries which have no
		 * values below.
		 */
		if (left->dummy && right->dummy)
			return 0;

		if (left->dummy || right->dummy)
			return left->dummy ? 1 : -1;
	}

	return __hist_entry__cmp_compute(p_left, p_right, c);
}