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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_inode {int dummy; } ;
struct xfs_ifork {int if_height; int if_bytes; } ;
struct xfs_iext_rec {int dummy; } ;
struct xfs_iext_leaf {int /*<<< orphan*/ * recs; } ;
struct xfs_iext_cursor {int pos; struct xfs_iext_leaf* leaf; } ;
struct xfs_bmbt_irec {int /*<<< orphan*/  br_startoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int RECS_PER_LEAF ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  cur_rec (struct xfs_iext_cursor*) ; 
 int /*<<< orphan*/  trace_xfs_iext_insert (struct xfs_inode*,struct xfs_iext_cursor*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_alloc_root (struct xfs_ifork*,struct xfs_iext_cursor*) ; 
 int /*<<< orphan*/  xfs_iext_inc_seq (struct xfs_ifork*) ; 
 int /*<<< orphan*/  xfs_iext_insert_node (struct xfs_ifork*,int /*<<< orphan*/ ,struct xfs_iext_leaf*,int) ; 
 int /*<<< orphan*/  xfs_iext_leaf_key (struct xfs_iext_leaf*,int /*<<< orphan*/ ) ; 
 int xfs_iext_leaf_nr_entries (struct xfs_ifork*,struct xfs_iext_leaf*,int) ; 
 int /*<<< orphan*/  xfs_iext_realloc_root (struct xfs_ifork*,struct xfs_iext_cursor*) ; 
 scalar_t__ xfs_iext_rec_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_set (int /*<<< orphan*/ ,struct xfs_bmbt_irec*) ; 
 struct xfs_iext_leaf* xfs_iext_split_leaf (struct xfs_iext_cursor*,int*) ; 
 struct xfs_ifork* xfs_iext_state_to_fork (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_iext_update_node (struct xfs_ifork*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_iext_leaf*) ; 

void
xfs_iext_insert(
	struct xfs_inode	*ip,
	struct xfs_iext_cursor	*cur,
	struct xfs_bmbt_irec	*irec,
	int			state)
{
	struct xfs_ifork	*ifp = xfs_iext_state_to_fork(ip, state);
	xfs_fileoff_t		offset = irec->br_startoff;
	struct xfs_iext_leaf	*new = NULL;
	int			nr_entries, i;

	xfs_iext_inc_seq(ifp);

	if (ifp->if_height == 0)
		xfs_iext_alloc_root(ifp, cur);
	else if (ifp->if_height == 1)
		xfs_iext_realloc_root(ifp, cur);

	nr_entries = xfs_iext_leaf_nr_entries(ifp, cur->leaf, cur->pos);
	ASSERT(nr_entries <= RECS_PER_LEAF);
	ASSERT(cur->pos >= nr_entries ||
	       xfs_iext_rec_cmp(cur_rec(cur), irec->br_startoff) != 0);

	if (nr_entries == RECS_PER_LEAF)
		new = xfs_iext_split_leaf(cur, &nr_entries);

	/*
	 * Update the pointers in higher levels if the first entry changes
	 * in an existing node.
	 */
	if (cur->leaf != new && cur->pos == 0 && nr_entries > 0) {
		xfs_iext_update_node(ifp, xfs_iext_leaf_key(cur->leaf, 0),
				offset, 1, cur->leaf);
	}

	for (i = nr_entries; i > cur->pos; i--)
		cur->leaf->recs[i] = cur->leaf->recs[i - 1];
	xfs_iext_set(cur_rec(cur), irec);
	ifp->if_bytes += sizeof(struct xfs_iext_rec);

	trace_xfs_iext_insert(ip, cur, state, _RET_IP_);

	if (new)
		xfs_iext_insert_node(ifp, xfs_iext_leaf_key(new, 0), new, 2);
}