#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int min_idx_lebs; long long data_growth; long long dd_growth; } ;
struct TYPE_3__ {int idx_lebs; int empty_lebs; int taken_empty_lebs; } ;
struct ubifs_info {int freeable_cnt; int idx_gc_cnt; long long rp_size; TYPE_2__ bi; TYPE_1__ lst; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  can_use_rp (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_budg (char*,long long,long long,...) ; 
 long long ubifs_calc_available (struct ubifs_info*,int) ; 
 int ubifs_calc_min_idx_lebs (struct ubifs_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_budget_space(struct ubifs_info *c)
{
	long long outstanding, available;
	int lebs, rsvd_idx_lebs, min_idx_lebs;

	/* First budget index space */
	min_idx_lebs = ubifs_calc_min_idx_lebs(c);

	/* Now 'min_idx_lebs' contains number of LEBs to reserve */
	if (min_idx_lebs > c->lst.idx_lebs)
		rsvd_idx_lebs = min_idx_lebs - c->lst.idx_lebs;
	else
		rsvd_idx_lebs = 0;

	/*
	 * The number of LEBs that are available to be used by the index is:
	 *
	 *    @c->lst.empty_lebs + @c->freeable_cnt + @c->idx_gc_cnt -
	 *    @c->lst.taken_empty_lebs
	 *
	 * @c->lst.empty_lebs are available because they are empty.
	 * @c->freeable_cnt are available because they contain only free and
	 * dirty space, @c->idx_gc_cnt are available because they are index
	 * LEBs that have been garbage collected and are awaiting the commit
	 * before they can be used. And the in-the-gaps method will grab these
	 * if it needs them. @c->lst.taken_empty_lebs are empty LEBs that have
	 * already been allocated for some purpose.
	 *
	 * Note, @c->idx_gc_cnt is included to both @c->lst.empty_lebs (because
	 * these LEBs are empty) and to @c->lst.taken_empty_lebs (because they
	 * are taken until after the commit).
	 *
	 * Note, @c->lst.taken_empty_lebs may temporarily be higher by one
	 * because of the way we serialize LEB allocations and budgeting. See a
	 * comment in 'ubifs_find_free_space()'.
	 */
	lebs = c->lst.empty_lebs + c->freeable_cnt + c->idx_gc_cnt -
	       c->lst.taken_empty_lebs;
	if (unlikely(rsvd_idx_lebs > lebs)) {
		dbg_budg("out of indexing space: min_idx_lebs %d (old %d), rsvd_idx_lebs %d",
			 min_idx_lebs, c->bi.min_idx_lebs, rsvd_idx_lebs);
		return -ENOSPC;
	}

	available = ubifs_calc_available(c, min_idx_lebs);
	outstanding = c->bi.data_growth + c->bi.dd_growth;

	if (unlikely(available < outstanding)) {
		dbg_budg("out of data space: available %lld, outstanding %lld",
			 available, outstanding);
		return -ENOSPC;
	}

	if (available - outstanding <= c->rp_size && !can_use_rp(c))
		return -ENOSPC;

	c->bi.min_idx_lebs = min_idx_lebs;
	return 0;
}