#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_da_state_blk {scalar_t__ magic; int /*<<< orphan*/  index; int /*<<< orphan*/  bp; } ;
struct TYPE_4__ {int active; struct xfs_da_state_blk* blk; } ;
struct xfs_da_state {int extravalid; TYPE_2__ path; int /*<<< orphan*/  extrablk; int /*<<< orphan*/  mp; struct xfs_da_args* args; } ;
struct xfs_da_args {TYPE_1__* dp; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EEXIST ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  trace_xfs_dir2_node_removename (struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_da3_fixhashpath (struct xfs_da_state*,TYPE_2__*) ; 
 int xfs_da3_join (struct xfs_da_state*) ; 
 int xfs_da3_node_lookup_int (struct xfs_da_state*,int*) ; 
 struct xfs_da_state* xfs_da_state_alloc () ; 
 int /*<<< orphan*/  xfs_da_state_free (struct xfs_da_state*) ; 
 int xfs_dir2_leafn_remove (struct xfs_da_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int xfs_dir2_node_to_leaf (struct xfs_da_state*) ; 

int						/* error */
xfs_dir2_node_removename(
	struct xfs_da_args	*args)		/* operation arguments */
{
	struct xfs_da_state_blk	*blk;		/* leaf block */
	int			error;		/* error return value */
	int			rval;		/* operation return value */
	struct xfs_da_state	*state;		/* btree cursor */

	trace_xfs_dir2_node_removename(args);

	/*
	 * Allocate and initialize the btree cursor.
	 */
	state = xfs_da_state_alloc();
	state->args = args;
	state->mp = args->dp->i_mount;

	/* Look up the entry we're deleting, set up the cursor. */
	error = xfs_da3_node_lookup_int(state, &rval);
	if (error)
		goto out_free;

	/* Didn't find it, upper layer screwed up. */
	if (rval != -EEXIST) {
		error = rval;
		goto out_free;
	}

	blk = &state->path.blk[state->path.active - 1];
	ASSERT(blk->magic == XFS_DIR2_LEAFN_MAGIC);
	ASSERT(state->extravalid);
	/*
	 * Remove the leaf and data entries.
	 * Extrablk refers to the data block.
	 */
	error = xfs_dir2_leafn_remove(args, blk->bp, blk->index,
		&state->extrablk, &rval);
	if (error)
		goto out_free;
	/*
	 * Fix the hash values up the btree.
	 */
	xfs_da3_fixhashpath(state, &state->path);
	/*
	 * If we need to join leaf blocks, do it.
	 */
	if (rval && state->path.active > 1)
		error = xfs_da3_join(state);
	/*
	 * If no errors so far, try conversion to leaf format.
	 */
	if (!error)
		error = xfs_dir2_node_to_leaf(state);
out_free:
	xfs_da_state_free(state);
	return error;
}