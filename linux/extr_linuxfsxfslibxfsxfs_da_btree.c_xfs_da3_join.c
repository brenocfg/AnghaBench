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
struct xfs_da_state_blk {scalar_t__ magic; int /*<<< orphan*/ * bp; int /*<<< orphan*/  blkno; } ;
struct TYPE_2__ {size_t active; struct xfs_da_state_blk* blk; } ;
struct xfs_da_state {TYPE_1__ path; int /*<<< orphan*/  args; TYPE_1__ altpath; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  XFS_ATTR_LEAF_MAGIC 130 
#define  XFS_DA_NODE_MAGIC 129 
#define  XFS_DIR2_LEAFN_MAGIC 128 
 int /*<<< orphan*/  trace_xfs_da_join (int /*<<< orphan*/ ) ; 
 int xfs_attr3_leaf_toosmall (struct xfs_da_state*,int*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_unbalance (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int xfs_da3_blk_unlink (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int /*<<< orphan*/  xfs_da3_fixhashpath (struct xfs_da_state*,TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_da3_node_remove (struct xfs_da_state*,struct xfs_da_state_blk*) ; 
 int xfs_da3_node_toosmall (struct xfs_da_state*,int*) ; 
 int /*<<< orphan*/  xfs_da3_node_unbalance (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int xfs_da3_root_join (struct xfs_da_state*,struct xfs_da_state_blk*) ; 
 int xfs_da_shrink_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_da_state_kill_altpath (struct xfs_da_state*) ; 
 int xfs_dir2_leafn_toosmall (struct xfs_da_state*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_unbalance (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 

int
xfs_da3_join(
	struct xfs_da_state	*state)
{
	struct xfs_da_state_blk	*drop_blk;
	struct xfs_da_state_blk	*save_blk;
	int			action = 0;
	int			error;

	trace_xfs_da_join(state->args);

	drop_blk = &state->path.blk[ state->path.active-1 ];
	save_blk = &state->altpath.blk[ state->path.active-1 ];
	ASSERT(state->path.blk[0].magic == XFS_DA_NODE_MAGIC);
	ASSERT(drop_blk->magic == XFS_ATTR_LEAF_MAGIC ||
	       drop_blk->magic == XFS_DIR2_LEAFN_MAGIC);

	/*
	 * Walk back up the tree joining/deallocating as necessary.
	 * When we stop dropping blocks, break out.
	 */
	for (  ; state->path.active >= 2; drop_blk--, save_blk--,
		 state->path.active--) {
		/*
		 * See if we can combine the block with a neighbor.
		 *   (action == 0) => no options, just leave
		 *   (action == 1) => coalesce, then unlink
		 *   (action == 2) => block empty, unlink it
		 */
		switch (drop_blk->magic) {
		case XFS_ATTR_LEAF_MAGIC:
			error = xfs_attr3_leaf_toosmall(state, &action);
			if (error)
				return error;
			if (action == 0)
				return 0;
			xfs_attr3_leaf_unbalance(state, drop_blk, save_blk);
			break;
		case XFS_DIR2_LEAFN_MAGIC:
			error = xfs_dir2_leafn_toosmall(state, &action);
			if (error)
				return error;
			if (action == 0)
				return 0;
			xfs_dir2_leafn_unbalance(state, drop_blk, save_blk);
			break;
		case XFS_DA_NODE_MAGIC:
			/*
			 * Remove the offending node, fixup hashvals,
			 * check for a toosmall neighbor.
			 */
			xfs_da3_node_remove(state, drop_blk);
			xfs_da3_fixhashpath(state, &state->path);
			error = xfs_da3_node_toosmall(state, &action);
			if (error)
				return error;
			if (action == 0)
				return 0;
			xfs_da3_node_unbalance(state, drop_blk, save_blk);
			break;
		}
		xfs_da3_fixhashpath(state, &state->altpath);
		error = xfs_da3_blk_unlink(state, drop_blk, save_blk);
		xfs_da_state_kill_altpath(state);
		if (error)
			return error;
		error = xfs_da_shrink_inode(state->args, drop_blk->blkno,
							 drop_blk->bp);
		drop_blk->bp = NULL;
		if (error)
			return error;
	}
	/*
	 * We joined all the way to the top.  If it turns out that
	 * we only have one entry in the root, make the child block
	 * the new root.
	 */
	xfs_da3_node_remove(state, drop_blk);
	xfs_da3_fixhashpath(state, &state->path);
	error = xfs_da3_root_join(state, &state->path.blk[0]);
	return error;
}