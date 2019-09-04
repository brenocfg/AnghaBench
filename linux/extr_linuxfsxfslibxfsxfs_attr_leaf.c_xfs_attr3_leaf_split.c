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
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_da_state_blk {scalar_t__ magic; int /*<<< orphan*/  bp; void* hashval; int /*<<< orphan*/  blkno; } ;
struct xfs_da_state {int /*<<< orphan*/  args; scalar_t__ inleaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_add_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_add_old (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_split (int /*<<< orphan*/ ) ; 
 int xfs_attr3_leaf_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_attr3_leaf_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_rebalance (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 void* xfs_attr_leaf_lasthash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_da3_blk_link (struct xfs_da_state*,struct xfs_da_state_blk*,struct xfs_da_state_blk*) ; 
 int xfs_da_grow_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xfs_attr3_leaf_split(
	struct xfs_da_state	*state,
	struct xfs_da_state_blk	*oldblk,
	struct xfs_da_state_blk	*newblk)
{
	xfs_dablk_t blkno;
	int error;

	trace_xfs_attr_leaf_split(state->args);

	/*
	 * Allocate space for a new leaf node.
	 */
	ASSERT(oldblk->magic == XFS_ATTR_LEAF_MAGIC);
	error = xfs_da_grow_inode(state->args, &blkno);
	if (error)
		return error;
	error = xfs_attr3_leaf_create(state->args, blkno, &newblk->bp);
	if (error)
		return error;
	newblk->blkno = blkno;
	newblk->magic = XFS_ATTR_LEAF_MAGIC;

	/*
	 * Rebalance the entries across the two leaves.
	 * NOTE: rebalance() currently depends on the 2nd block being empty.
	 */
	xfs_attr3_leaf_rebalance(state, oldblk, newblk);
	error = xfs_da3_blk_link(state, oldblk, newblk);
	if (error)
		return error;

	/*
	 * Save info on "old" attribute for "atomic rename" ops, leaf_add()
	 * modifies the index/blkno/rmtblk/rmtblkcnt fields to show the
	 * "new" attrs info.  Will need the "old" info to remove it later.
	 *
	 * Insert the "new" entry in the correct block.
	 */
	if (state->inleaf) {
		trace_xfs_attr_leaf_add_old(state->args);
		error = xfs_attr3_leaf_add(oldblk->bp, state->args);
	} else {
		trace_xfs_attr_leaf_add_new(state->args);
		error = xfs_attr3_leaf_add(newblk->bp, state->args);
	}

	/*
	 * Update last hashval in each block since we added the name.
	 */
	oldblk->hashval = xfs_attr_leaf_lasthash(oldblk->bp, NULL);
	newblk->hashval = xfs_attr_leaf_lasthash(newblk->bp, NULL);
	return error;
}