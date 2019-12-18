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
struct ubifs_lprops {int flags; int /*<<< orphan*/  free; int /*<<< orphan*/  dirty; int /*<<< orphan*/  lnum; } ;
struct TYPE_2__ {size_t cnt; scalar_t__* arr; } ;
struct ubifs_info {TYPE_1__ dirty_idx; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int LPROPS_INDEX ; 
 int /*<<< orphan*/  LPROPS_NC ; 
 int LPROPS_TAKEN ; 
 int PTR_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  dbg_find (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct ubifs_lprops* ubifs_change_lp (struct ubifs_info*,struct ubifs_lprops const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ubifs_lprops* ubifs_lpt_lookup (struct ubifs_info*,int) ; 

__attribute__((used)) static int find_dirtiest_idx_leb(struct ubifs_info *c)
{
	const struct ubifs_lprops *lp;
	int lnum;

	while (1) {
		if (!c->dirty_idx.cnt)
			return -ENOSPC;
		/* The lprops pointers were replaced by LEB numbers */
		lnum = (size_t)c->dirty_idx.arr[--c->dirty_idx.cnt];
		lp = ubifs_lpt_lookup(c, lnum);
		if (IS_ERR(lp))
			return PTR_ERR(lp);
		if ((lp->flags & LPROPS_TAKEN) || !(lp->flags & LPROPS_INDEX))
			continue;
		lp = ubifs_change_lp(c, lp, LPROPS_NC, LPROPS_NC,
				     lp->flags | LPROPS_TAKEN, 0);
		if (IS_ERR(lp))
			return PTR_ERR(lp);
		break;
	}
	dbg_find("LEB %d, dirty %d and free %d flags %#x", lp->lnum, lp->dirty,
		 lp->free, lp->flags);
	ubifs_assert(c, lp->flags & LPROPS_TAKEN);
	ubifs_assert(c, lp->flags & LPROPS_INDEX);
	return lnum;
}