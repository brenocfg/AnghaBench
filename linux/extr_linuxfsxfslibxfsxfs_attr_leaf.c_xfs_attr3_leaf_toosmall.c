#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_dablk_t ;
typedef  int /*<<< orphan*/  xfs_attr_leaf_entry_t ;
struct xfs_da_state_blk {scalar_t__ blkno; TYPE_1__* bp; } ;
struct TYPE_8__ {int active; struct xfs_da_state_blk* blk; } ;
struct xfs_da_state {TYPE_2__ path; TYPE_2__ altpath; TYPE_4__* args; } ;
struct xfs_buf {struct xfs_attr_leafblock* b_addr; } ;
struct xfs_attr_leafblock {int dummy; } ;
struct xfs_attr3_icleaf_hdr {int count; int usedbytes; scalar_t__ forw; scalar_t__ back; } ;
struct TYPE_10__ {int /*<<< orphan*/  trans; TYPE_3__* geo; int /*<<< orphan*/  dp; } ;
struct TYPE_9__ {int blksize; } ;
struct TYPE_7__ {struct xfs_attr_leafblock* b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_toosmall (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (TYPE_3__*,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 int xfs_attr3_leaf_hdr_size (struct xfs_attr_leafblock*) ; 
 int xfs_attr3_leaf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,struct xfs_buf**) ; 
 int xfs_da3_path_shift (struct xfs_da_state*,TYPE_2__*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,struct xfs_buf*) ; 

int
xfs_attr3_leaf_toosmall(
	struct xfs_da_state	*state,
	int			*action)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_da_state_blk	*blk;
	struct xfs_attr3_icleaf_hdr ichdr;
	struct xfs_buf		*bp;
	xfs_dablk_t		blkno;
	int			bytes;
	int			forward;
	int			error;
	int			retval;
	int			i;

	trace_xfs_attr_leaf_toosmall(state->args);

	/*
	 * Check for the degenerate case of the block being over 50% full.
	 * If so, it's not worth even looking to see if we might be able
	 * to coalesce with a sibling.
	 */
	blk = &state->path.blk[ state->path.active-1 ];
	leaf = blk->bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(state->args->geo, &ichdr, leaf);
	bytes = xfs_attr3_leaf_hdr_size(leaf) +
		ichdr.count * sizeof(xfs_attr_leaf_entry_t) +
		ichdr.usedbytes;
	if (bytes > (state->args->geo->blksize >> 1)) {
		*action = 0;	/* blk over 50%, don't try to join */
		return 0;
	}

	/*
	 * Check for the degenerate case of the block being empty.
	 * If the block is empty, we'll simply delete it, no need to
	 * coalesce it with a sibling block.  We choose (arbitrarily)
	 * to merge with the forward block unless it is NULL.
	 */
	if (ichdr.count == 0) {
		/*
		 * Make altpath point to the block we want to keep and
		 * path point to the block we want to drop (this one).
		 */
		forward = (ichdr.forw != 0);
		memcpy(&state->altpath, &state->path, sizeof(state->path));
		error = xfs_da3_path_shift(state, &state->altpath, forward,
						 0, &retval);
		if (error)
			return error;
		if (retval) {
			*action = 0;
		} else {
			*action = 2;
		}
		return 0;
	}

	/*
	 * Examine each sibling block to see if we can coalesce with
	 * at least 25% free space to spare.  We need to figure out
	 * whether to merge with the forward or the backward block.
	 * We prefer coalescing with the lower numbered sibling so as
	 * to shrink an attribute list over time.
	 */
	/* start with smaller blk num */
	forward = ichdr.forw < ichdr.back;
	for (i = 0; i < 2; forward = !forward, i++) {
		struct xfs_attr3_icleaf_hdr ichdr2;
		if (forward)
			blkno = ichdr.forw;
		else
			blkno = ichdr.back;
		if (blkno == 0)
			continue;
		error = xfs_attr3_leaf_read(state->args->trans, state->args->dp,
					blkno, -1, &bp);
		if (error)
			return error;

		xfs_attr3_leaf_hdr_from_disk(state->args->geo, &ichdr2, bp->b_addr);

		bytes = state->args->geo->blksize -
			(state->args->geo->blksize >> 2) -
			ichdr.usedbytes - ichdr2.usedbytes -
			((ichdr.count + ichdr2.count) *
					sizeof(xfs_attr_leaf_entry_t)) -
			xfs_attr3_leaf_hdr_size(leaf);

		xfs_trans_brelse(state->args->trans, bp);
		if (bytes >= 0)
			break;	/* fits with at least 25% to spare */
	}
	if (i >= 2) {
		*action = 0;
		return 0;
	}

	/*
	 * Make altpath point to the block we want to keep (the lower
	 * numbered block) and path point to the block we want to drop.
	 */
	memcpy(&state->altpath, &state->path, sizeof(state->path));
	if (blkno < blk->blkno) {
		error = xfs_da3_path_shift(state, &state->altpath, forward,
						 0, &retval);
	} else {
		error = xfs_da3_path_shift(state, &state->path, forward,
						 0, &retval);
	}
	if (error)
		return error;
	if (retval) {
		*action = 0;
	} else {
		*action = 1;
	}
	return 0;
}