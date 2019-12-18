#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
typedef  scalar_t__ xfs_dablk_t ;
struct TYPE_18__ {int active; TYPE_5__* blk; } ;
struct TYPE_15__ {TYPE_9__ path; TYPE_9__ altpath; TYPE_3__* args; } ;
typedef  TYPE_4__ xfs_da_state_t ;
struct TYPE_16__ {scalar_t__ blkno; TYPE_6__* bp; } ;
typedef  TYPE_5__ xfs_da_state_blk_t ;
struct xfs_inode {TYPE_2__* d_ops; } ;
struct xfs_dir3_icleaf_hdr {int count; int stale; scalar_t__ forw; scalar_t__ back; } ;
struct xfs_dir2_leaf_entry {int dummy; } ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
typedef  int /*<<< orphan*/  ents ;
struct TYPE_17__ {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  trans; TYPE_1__* geo; struct xfs_inode* dp; } ;
struct TYPE_13__ {int leaf_hdr_size; struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int blksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_9__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 struct xfs_dir2_leaf_entry* stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 struct xfs_dir2_leaf_entry* stub4 (int /*<<< orphan*/ *) ; 
 int xfs_da3_path_shift (TYPE_4__*,TYPE_9__*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (struct xfs_inode*,TYPE_6__*) ; 
 int xfs_dir3_leafn_read (int /*<<< orphan*/ ,struct xfs_inode*,scalar_t__,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_leafn_toosmall(
	xfs_da_state_t		*state,		/* btree cursor */
	int			*action)	/* resulting action to take */
{
	xfs_da_state_blk_t	*blk;		/* leaf block */
	xfs_dablk_t		blkno;		/* leaf block number */
	struct xfs_buf		*bp;		/* leaf buffer */
	int			bytes;		/* bytes in use */
	int			count;		/* leaf live entry count */
	int			error;		/* error return value */
	int			forward;	/* sibling block direction */
	int			i;		/* sibling counter */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	int			rval;		/* result from path_shift */
	struct xfs_dir3_icleaf_hdr leafhdr;
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_inode	*dp = state->args->dp;

	/*
	 * Check for the degenerate case of the block being over 50% full.
	 * If so, it's not worth even looking to see if we might be able
	 * to coalesce with a sibling.
	 */
	blk = &state->path.blk[state->path.active - 1];
	leaf = blk->bp->b_addr;
	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);
	ents = dp->d_ops->leaf_ents_p(leaf);
	xfs_dir3_leaf_check(dp, blk->bp);

	count = leafhdr.count - leafhdr.stale;
	bytes = dp->d_ops->leaf_hdr_size + count * sizeof(ents[0]);
	if (bytes > (state->args->geo->blksize >> 1)) {
		/*
		 * Blk over 50%, don't try to join.
		 */
		*action = 0;
		return 0;
	}
	/*
	 * Check for the degenerate case of the block being empty.
	 * If the block is empty, we'll simply delete it, no need to
	 * coalesce it with a sibling block.  We choose (arbitrarily)
	 * to merge with the forward block unless it is NULL.
	 */
	if (count == 0) {
		/*
		 * Make altpath point to the block we want to keep and
		 * path point to the block we want to drop (this one).
		 */
		forward = (leafhdr.forw != 0);
		memcpy(&state->altpath, &state->path, sizeof(state->path));
		error = xfs_da3_path_shift(state, &state->altpath, forward, 0,
			&rval);
		if (error)
			return error;
		*action = rval ? 2 : 0;
		return 0;
	}
	/*
	 * Examine each sibling block to see if we can coalesce with
	 * at least 25% free space to spare.  We need to figure out
	 * whether to merge with the forward or the backward block.
	 * We prefer coalescing with the lower numbered sibling so as
	 * to shrink a directory over time.
	 */
	forward = leafhdr.forw < leafhdr.back;
	for (i = 0, bp = NULL; i < 2; forward = !forward, i++) {
		struct xfs_dir3_icleaf_hdr hdr2;

		blkno = forward ? leafhdr.forw : leafhdr.back;
		if (blkno == 0)
			continue;
		/*
		 * Read the sibling leaf block.
		 */
		error = xfs_dir3_leafn_read(state->args->trans, dp,
					    blkno, -1, &bp);
		if (error)
			return error;

		/*
		 * Count bytes in the two blocks combined.
		 */
		count = leafhdr.count - leafhdr.stale;
		bytes = state->args->geo->blksize -
			(state->args->geo->blksize >> 2);

		leaf = bp->b_addr;
		dp->d_ops->leaf_hdr_from_disk(&hdr2, leaf);
		ents = dp->d_ops->leaf_ents_p(leaf);
		count += hdr2.count - hdr2.stale;
		bytes -= count * sizeof(ents[0]);

		/*
		 * Fits with at least 25% to spare.
		 */
		if (bytes >= 0)
			break;
		xfs_trans_brelse(state->args->trans, bp);
	}
	/*
	 * Didn't like either block, give up.
	 */
	if (i >= 2) {
		*action = 0;
		return 0;
	}

	/*
	 * Make altpath point to the block we want to keep (the lower
	 * numbered block) and path point to the block we want to drop.
	 */
	memcpy(&state->altpath, &state->path, sizeof(state->path));
	if (blkno < blk->blkno)
		error = xfs_da3_path_shift(state, &state->altpath, forward, 0,
			&rval);
	else
		error = xfs_da3_path_shift(state, &state->path, forward, 0,
			&rval);
	if (error) {
		return error;
	}
	*action = rval ? 0 : 1;
	return 0;
}