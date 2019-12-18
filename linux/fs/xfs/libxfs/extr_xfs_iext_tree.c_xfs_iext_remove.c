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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * if_root; } ;
struct xfs_ifork {int if_height; int if_bytes; TYPE_1__ if_u1; } ;
struct xfs_iext_rec {int dummy; } ;
struct xfs_iext_leaf {struct xfs_iext_leaf* next; int /*<<< orphan*/ * recs; } ;
struct xfs_iext_cursor {int pos; struct xfs_iext_leaf* leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int RECS_PER_LEAF ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_iext_remove (struct xfs_inode*,struct xfs_iext_cursor*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_free_last_leaf (struct xfs_ifork*) ; 
 int /*<<< orphan*/  xfs_iext_inc_seq (struct xfs_ifork*) ; 
 int /*<<< orphan*/  xfs_iext_leaf_key (struct xfs_iext_leaf*,int /*<<< orphan*/ ) ; 
 int xfs_iext_leaf_nr_entries (struct xfs_ifork*,struct xfs_iext_leaf*,int) ; 
 int /*<<< orphan*/  xfs_iext_rebalance_leaf (struct xfs_ifork*,struct xfs_iext_cursor*,struct xfs_iext_leaf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_iext_rec_clear (int /*<<< orphan*/ *) ; 
 struct xfs_ifork* xfs_iext_state_to_fork (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_iext_update_node (struct xfs_ifork*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_iext_leaf*) ; 
 int xfs_iext_valid (struct xfs_ifork*,struct xfs_iext_cursor*) ; 

void
xfs_iext_remove(
	struct xfs_inode	*ip,
	struct xfs_iext_cursor	*cur,
	int			state)
{
	struct xfs_ifork	*ifp = xfs_iext_state_to_fork(ip, state);
	struct xfs_iext_leaf	*leaf = cur->leaf;
	xfs_fileoff_t		offset = xfs_iext_leaf_key(leaf, 0);
	int			i, nr_entries;

	trace_xfs_iext_remove(ip, cur, state, _RET_IP_);

	ASSERT(ifp->if_height > 0);
	ASSERT(ifp->if_u1.if_root != NULL);
	ASSERT(xfs_iext_valid(ifp, cur));

	xfs_iext_inc_seq(ifp);

	nr_entries = xfs_iext_leaf_nr_entries(ifp, leaf, cur->pos) - 1;
	for (i = cur->pos; i < nr_entries; i++)
		leaf->recs[i] = leaf->recs[i + 1];
	xfs_iext_rec_clear(&leaf->recs[nr_entries]);
	ifp->if_bytes -= sizeof(struct xfs_iext_rec);

	if (cur->pos == 0 && nr_entries > 0) {
		xfs_iext_update_node(ifp, offset, xfs_iext_leaf_key(leaf, 0), 1,
				leaf);
		offset = xfs_iext_leaf_key(leaf, 0);
	} else if (cur->pos == nr_entries) {
		if (ifp->if_height > 1 && leaf->next)
			cur->leaf = leaf->next;
		else
			cur->leaf = NULL;
		cur->pos = 0;
	}

	if (nr_entries >= RECS_PER_LEAF / 2)
		return;

	if (ifp->if_height > 1)
		xfs_iext_rebalance_leaf(ifp, cur, leaf, offset, nr_entries);
	else if (nr_entries == 0)
		xfs_iext_free_last_leaf(ifp);
}