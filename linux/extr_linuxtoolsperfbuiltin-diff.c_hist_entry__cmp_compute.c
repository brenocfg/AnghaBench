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
struct hist_entry {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int __hist_entry__cmp_compute (struct hist_entry*,struct hist_entry*,int) ; 
 int /*<<< orphan*/ * data__files ; 
 struct hist_entry* get_pair_data (struct hist_entry*,int /*<<< orphan*/ *) ; 
 int hist_entry__has_pairs (struct hist_entry*) ; 

__attribute__((used)) static int64_t
hist_entry__cmp_compute(struct hist_entry *left, struct hist_entry *right,
			int c, int sort_idx)
{
	bool pairs_left  = hist_entry__has_pairs(left);
	bool pairs_right = hist_entry__has_pairs(right);
	struct hist_entry *p_right, *p_left;

	if (!pairs_left && !pairs_right)
		return 0;

	if (!pairs_left || !pairs_right)
		return pairs_left ? -1 : 1;

	p_left  = get_pair_data(left,  &data__files[sort_idx]);
	p_right = get_pair_data(right, &data__files[sort_idx]);

	if (!p_left && !p_right)
		return 0;

	if (!p_left || !p_right)
		return p_left ? -1 : 1;

	/*
	 * We have 2 entries of same kind, let's
	 * make the data comparison.
	 */
	return __hist_entry__cmp_compute(p_left, p_right, c);
}