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
struct ubifs_lprops {int lnum; int flags; int /*<<< orphan*/  dirty; int /*<<< orphan*/  free; } ;
struct TYPE_2__ {scalar_t__ empty_lebs; scalar_t__ taken_empty_lebs; } ;
struct ubifs_info {scalar_t__ in_a_category_cnt; scalar_t__ main_lebs; scalar_t__ freeable_cnt; int /*<<< orphan*/  leb_size; TYPE_1__ lst; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int LPROPS_INDEX ; 
 int /*<<< orphan*/  LPROPS_NC ; 
 int LPROPS_TAKEN ; 
 int PTR_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  dbg_find (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ubifs_lprops* scan_for_leb_for_idx (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct ubifs_lprops* ubifs_change_lp (struct ubifs_info*,struct ubifs_lprops const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_change_one_lp (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ubifs_lprops* ubifs_fast_find_empty (struct ubifs_info*) ; 
 struct ubifs_lprops* ubifs_fast_find_freeable (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_get_lprops (struct ubifs_info*) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_release_lprops (struct ubifs_info*) ; 

int ubifs_find_free_leb_for_idx(struct ubifs_info *c)
{
	const struct ubifs_lprops *lprops;
	int lnum = -1, err, flags;

	ubifs_get_lprops(c);

	lprops = ubifs_fast_find_empty(c);
	if (!lprops) {
		lprops = ubifs_fast_find_freeable(c);
		if (!lprops) {
			/*
			 * The first condition means the following: go scan the
			 * LPT if there are uncategorized lprops, which means
			 * there may be freeable LEBs there (UBIFS does not
			 * store the information about freeable LEBs in the
			 * master node).
			 */
			if (c->in_a_category_cnt != c->main_lebs ||
			    c->lst.empty_lebs - c->lst.taken_empty_lebs > 0) {
				ubifs_assert(c, c->freeable_cnt == 0);
				lprops = scan_for_leb_for_idx(c);
				if (IS_ERR(lprops)) {
					err = PTR_ERR(lprops);
					goto out;
				}
			}
		}
	}

	if (!lprops) {
		err = -ENOSPC;
		goto out;
	}

	lnum = lprops->lnum;

	dbg_find("found LEB %d, free %d, dirty %d, flags %#x",
		 lnum, lprops->free, lprops->dirty, lprops->flags);

	flags = lprops->flags | LPROPS_TAKEN | LPROPS_INDEX;
	lprops = ubifs_change_lp(c, lprops, c->leb_size, 0, flags, 0);
	if (IS_ERR(lprops)) {
		err = PTR_ERR(lprops);
		goto out;
	}

	ubifs_release_lprops(c);

	/*
	 * Ensure that empty LEBs have been unmapped. They may not have been,
	 * for example, because of an unclean unmount. Also LEBs that were
	 * freeable LEBs (free + dirty == leb_size) will not have been unmapped.
	 */
	err = ubifs_leb_unmap(c, lnum);
	if (err) {
		ubifs_change_one_lp(c, lnum, LPROPS_NC, LPROPS_NC, 0,
				    LPROPS_TAKEN | LPROPS_INDEX, 0);
		return err;
	}

	return lnum;

out:
	ubifs_release_lprops(c);
	return err;
}