#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct TYPE_16__ {scalar_t__ inleaf; TYPE_3__* args; } ;
typedef  TYPE_1__ xfs_da_state_t ;
struct TYPE_17__ {scalar_t__ magic; int /*<<< orphan*/  bp; void* hashval; int /*<<< orphan*/  index; int /*<<< orphan*/  blkno; } ;
typedef  TYPE_2__ xfs_da_state_blk_t ;
struct TYPE_18__ {int /*<<< orphan*/  geo; struct xfs_inode* dp; } ;
typedef  TYPE_3__ xfs_da_args_t ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 int xfs_da3_blk_link (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int xfs_da_grow_inode (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir2_da_to_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xfs_dir2_leaf_lasthash (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_dir2_leafn_add (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_rebalance (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_dir3_leaf_get_buf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int						/* error */
xfs_dir2_leafn_split(
	xfs_da_state_t		*state,		/* btree cursor */
	xfs_da_state_blk_t	*oldblk,	/* original block */
	xfs_da_state_blk_t	*newblk)	/* newly created block */
{
	xfs_da_args_t		*args;		/* operation arguments */
	xfs_dablk_t		blkno;		/* new leaf block number */
	int			error;		/* error return value */
	struct xfs_inode	*dp;

	/*
	 * Allocate space for a new leaf node.
	 */
	args = state->args;
	dp = args->dp;
	ASSERT(oldblk->magic == XFS_DIR2_LEAFN_MAGIC);
	error = xfs_da_grow_inode(args, &blkno);
	if (error) {
		return error;
	}
	/*
	 * Initialize the new leaf block.
	 */
	error = xfs_dir3_leaf_get_buf(args, xfs_dir2_da_to_db(args->geo, blkno),
				      &newblk->bp, XFS_DIR2_LEAFN_MAGIC);
	if (error)
		return error;

	newblk->blkno = blkno;
	newblk->magic = XFS_DIR2_LEAFN_MAGIC;
	/*
	 * Rebalance the entries across the two leaves, link the new
	 * block into the leaves.
	 */
	xfs_dir2_leafn_rebalance(state, oldblk, newblk);
	error = xfs_da3_blk_link(state, oldblk, newblk);
	if (error) {
		return error;
	}
	/*
	 * Insert the new entry in the correct block.
	 */
	if (state->inleaf)
		error = xfs_dir2_leafn_add(oldblk->bp, args, oldblk->index);
	else
		error = xfs_dir2_leafn_add(newblk->bp, args, newblk->index);
	/*
	 * Update last hashval in each block since we added the name.
	 */
	oldblk->hashval = xfs_dir2_leaf_lasthash(dp, oldblk->bp, NULL);
	newblk->hashval = xfs_dir2_leaf_lasthash(dp, newblk->bp, NULL);
	xfs_dir3_leaf_check(dp, oldblk->bp);
	xfs_dir3_leaf_check(dp, newblk->bp);
	return error;
}