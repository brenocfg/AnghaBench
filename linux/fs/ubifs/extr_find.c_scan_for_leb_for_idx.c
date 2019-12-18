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
typedef  int /*<<< orphan*/  ubifs_lpt_scan_callback ;
struct ubifs_lprops {int lnum; scalar_t__ free; scalar_t__ dirty; int flags; } ;
struct ubifs_info {int lscan_lnum; int main_first; int leb_cnt; scalar_t__ leb_size; } ;
struct scan_data {int lnum; } ;

/* Variables and functions */
 struct ubifs_lprops const* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int LPROPS_INDEX ; 
 int LPROPS_TAKEN ; 
 scalar_t__ scan_for_idx_cb ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct ubifs_lprops* ubifs_lpt_lookup_dirty (struct ubifs_info*,int) ; 
 int ubifs_lpt_scan_nolock (struct ubifs_info*,int,int,int /*<<< orphan*/ ,struct scan_data*) ; 

__attribute__((used)) static const struct ubifs_lprops *scan_for_leb_for_idx(struct ubifs_info *c)
{
	const struct ubifs_lprops *lprops;
	struct scan_data data;
	int err;

	data.lnum = -1;
	err = ubifs_lpt_scan_nolock(c, -1, c->lscan_lnum,
				    (ubifs_lpt_scan_callback)scan_for_idx_cb,
				    &data);
	if (err)
		return ERR_PTR(err);
	ubifs_assert(c, data.lnum >= c->main_first && data.lnum < c->leb_cnt);
	c->lscan_lnum = data.lnum;
	lprops = ubifs_lpt_lookup_dirty(c, data.lnum);
	if (IS_ERR(lprops))
		return lprops;
	ubifs_assert(c, lprops->lnum == data.lnum);
	ubifs_assert(c, lprops->free + lprops->dirty == c->leb_size);
	ubifs_assert(c, !(lprops->flags & LPROPS_TAKEN));
	ubifs_assert(c, !(lprops->flags & LPROPS_INDEX));
	return lprops;
}