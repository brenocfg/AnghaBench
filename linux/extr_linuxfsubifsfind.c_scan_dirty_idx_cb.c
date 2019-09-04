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
struct ubifs_lprops {int flags; scalar_t__ free; scalar_t__ dirty; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {scalar_t__ min_idx_node_sz; } ;
struct scan_data {int /*<<< orphan*/  lnum; } ;

/* Variables and functions */
 int LPROPS_INDEX ; 
 int LPROPS_TAKEN ; 
 int LPT_SCAN_ADD ; 
 int LPT_SCAN_CONTINUE ; 
 int LPT_SCAN_STOP ; 
 scalar_t__ valuable (struct ubifs_info*,struct ubifs_lprops const*) ; 

__attribute__((used)) static int scan_dirty_idx_cb(struct ubifs_info *c,
			   const struct ubifs_lprops *lprops, int in_tree,
			   struct scan_data *data)
{
	int ret = LPT_SCAN_CONTINUE;

	/* Exclude LEBs that are currently in use */
	if (lprops->flags & LPROPS_TAKEN)
		return LPT_SCAN_CONTINUE;
	/* Determine whether to add these LEB properties to the tree */
	if (!in_tree && valuable(c, lprops))
		ret |= LPT_SCAN_ADD;
	/* Exclude non-index LEBs */
	if (!(lprops->flags & LPROPS_INDEX))
		return ret;
	/* Exclude LEBs with too little space */
	if (lprops->free + lprops->dirty < c->min_idx_node_sz)
		return ret;
	/* Finally we found space */
	data->lnum = lprops->lnum;
	return LPT_SCAN_ADD | LPT_SCAN_STOP;
}