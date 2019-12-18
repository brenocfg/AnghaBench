#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct xfs_da_state_blk {scalar_t__ magic; scalar_t__ blkno; TYPE_3__* bp; } ;
struct TYPE_12__ {int active; struct xfs_da_state_blk* blk; } ;
struct TYPE_9__ {struct xfs_da_state_blk* blk; } ;
struct xfs_da_state {int extravalid; int extraafter; TYPE_5__* args; TYPE_4__ path; struct xfs_da_state_blk extrablk; int /*<<< orphan*/  inleaf; TYPE_1__ altpath; } ;
struct TYPE_14__ {void* forw; void* back; } ;
struct TYPE_10__ {TYPE_8__ info; } ;
struct xfs_da_intnode {TYPE_2__ hdr; } ;
struct TYPE_13__ {int /*<<< orphan*/  trans; } ;
struct TYPE_11__ {struct xfs_da_intnode* b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int ENOSPC ; 
#define  XFS_ATTR_LEAF_MAGIC 130 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (struct xfs_da_intnode*,TYPE_8__*,int) ; 
#define  XFS_DA_NODE_MAGIC 129 
 int XFS_DA_NODE_MAXDEPTH ; 
#define  XFS_DIR2_LEAFN_MAGIC 128 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_split_after (TYPE_5__*) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_split_before (TYPE_5__*) ; 
 int /*<<< orphan*/  trace_xfs_da_split (TYPE_5__*) ; 
 int xfs_attr3_leaf_split (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int /*<<< orphan*/  xfs_da3_fixhashpath (struct xfs_da_state*,TYPE_4__*) ; 
 int xfs_da3_node_split (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*,struct xfs_da_state_blk*,int,int*) ; 
 int xfs_da3_root_split (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int xfs_dir2_leafn_split (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

int							/* error */
xfs_da3_split(
	struct xfs_da_state	*state)
{
	struct xfs_da_state_blk	*oldblk;
	struct xfs_da_state_blk	*newblk;
	struct xfs_da_state_blk	*addblk;
	struct xfs_da_intnode	*node;
	int			max;
	int			action = 0;
	int			error;
	int			i;

	trace_xfs_da_split(state->args);

	/*
	 * Walk back up the tree splitting/inserting/adjusting as necessary.
	 * If we need to insert and there isn't room, split the node, then
	 * decide which fragment to insert the new block from below into.
	 * Note that we may split the root this way, but we need more fixup.
	 */
	max = state->path.active - 1;
	ASSERT((max >= 0) && (max < XFS_DA_NODE_MAXDEPTH));
	ASSERT(state->path.blk[max].magic == XFS_ATTR_LEAF_MAGIC ||
	       state->path.blk[max].magic == XFS_DIR2_LEAFN_MAGIC);

	addblk = &state->path.blk[max];		/* initial dummy value */
	for (i = max; (i >= 0) && addblk; state->path.active--, i--) {
		oldblk = &state->path.blk[i];
		newblk = &state->altpath.blk[i];

		/*
		 * If a leaf node then
		 *     Allocate a new leaf node, then rebalance across them.
		 * else if an intermediate node then
		 *     We split on the last layer, must we split the node?
		 */
		switch (oldblk->magic) {
		case XFS_ATTR_LEAF_MAGIC:
			error = xfs_attr3_leaf_split(state, oldblk, newblk);
			if ((error != 0) && (error != -ENOSPC)) {
				return error;	/* GROT: attr is inconsistent */
			}
			if (!error) {
				addblk = newblk;
				break;
			}
			/*
			 * Entry wouldn't fit, split the leaf again. The new
			 * extrablk will be consumed by xfs_da3_node_split if
			 * the node is split.
			 */
			state->extravalid = 1;
			if (state->inleaf) {
				state->extraafter = 0;	/* before newblk */
				trace_xfs_attr_leaf_split_before(state->args);
				error = xfs_attr3_leaf_split(state, oldblk,
							    &state->extrablk);
			} else {
				state->extraafter = 1;	/* after newblk */
				trace_xfs_attr_leaf_split_after(state->args);
				error = xfs_attr3_leaf_split(state, newblk,
							    &state->extrablk);
			}
			if (error)
				return error;	/* GROT: attr inconsistent */
			addblk = newblk;
			break;
		case XFS_DIR2_LEAFN_MAGIC:
			error = xfs_dir2_leafn_split(state, oldblk, newblk);
			if (error)
				return error;
			addblk = newblk;
			break;
		case XFS_DA_NODE_MAGIC:
			error = xfs_da3_node_split(state, oldblk, newblk, addblk,
							 max - i, &action);
			addblk->bp = NULL;
			if (error)
				return error;	/* GROT: dir is inconsistent */
			/*
			 * Record the newly split block for the next time thru?
			 */
			if (action)
				addblk = newblk;
			else
				addblk = NULL;
			break;
		}

		/*
		 * Update the btree to show the new hashval for this child.
		 */
		xfs_da3_fixhashpath(state, &state->path);
	}
	if (!addblk)
		return 0;

	/*
	 * xfs_da3_node_split() should have consumed any extra blocks we added
	 * during a double leaf split in the attr fork. This is guaranteed as
	 * we can't be here if the attr fork only has a single leaf block.
	 */
	ASSERT(state->extravalid == 0 ||
	       state->path.blk[max].magic == XFS_DIR2_LEAFN_MAGIC);

	/*
	 * Split the root node.
	 */
	ASSERT(state->path.active == 0);
	oldblk = &state->path.blk[0];
	error = xfs_da3_root_split(state, oldblk, addblk);
	if (error)
		goto out;

	/*
	 * Update pointers to the node which used to be block 0 and just got
	 * bumped because of the addition of a new root node.  Note that the
	 * original block 0 could be at any position in the list of blocks in
	 * the tree.
	 *
	 * Note: the magic numbers and sibling pointers are in the same physical
	 * place for both v2 and v3 headers (by design). Hence it doesn't matter
	 * which version of the xfs_da_intnode structure we use here as the
	 * result will be the same using either structure.
	 */
	node = oldblk->bp->b_addr;
	if (node->hdr.info.forw) {
		if (be32_to_cpu(node->hdr.info.forw) != addblk->blkno) {
			error = -EFSCORRUPTED;
			goto out;
		}
		node = addblk->bp->b_addr;
		node->hdr.info.back = cpu_to_be32(oldblk->blkno);
		xfs_trans_log_buf(state->args->trans, addblk->bp,
				  XFS_DA_LOGRANGE(node, &node->hdr.info,
				  sizeof(node->hdr.info)));
	}
	node = oldblk->bp->b_addr;
	if (node->hdr.info.back) {
		if (be32_to_cpu(node->hdr.info.back) != addblk->blkno) {
			error = -EFSCORRUPTED;
			goto out;
		}
		node = addblk->bp->b_addr;
		node->hdr.info.forw = cpu_to_be32(oldblk->blkno);
		xfs_trans_log_buf(state->args->trans, addblk->bp,
				  XFS_DA_LOGRANGE(node, &node->hdr.info,
				  sizeof(node->hdr.info)));
	}
out:
	addblk->bp = NULL;
	return error;
}