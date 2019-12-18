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
struct TYPE_2__ {scalar_t__ di_aformat; scalar_t__ di_anextents; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct xfs_da_args {int /*<<< orphan*/  trans; struct xfs_inode* dp; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_EXTENTS ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int xfs_attr_leaf_addname (struct xfs_da_args*) ; 
 int xfs_attr_node_addname (struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_attr_shortform_create (struct xfs_da_args*) ; 
 int xfs_attr_shortform_to_leaf (struct xfs_da_args*,struct xfs_buf**) ; 
 int xfs_attr_try_sf_addname (struct xfs_inode*,struct xfs_da_args*) ; 
 scalar_t__ xfs_bmap_one_block (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_defer_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_bhold (int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_bhold_release (int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,struct xfs_buf*) ; 

int
xfs_attr_set_args(
	struct xfs_da_args	*args)
{
	struct xfs_inode	*dp = args->dp;
	struct xfs_buf          *leaf_bp = NULL;
	int			error;

	/*
	 * If the attribute list is non-existent or a shortform list,
	 * upgrade it to a single-leaf-block attribute list.
	 */
	if (dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL ||
	    (dp->i_d.di_aformat == XFS_DINODE_FMT_EXTENTS &&
	     dp->i_d.di_anextents == 0)) {

		/*
		 * Build initial attribute list (if required).
		 */
		if (dp->i_d.di_aformat == XFS_DINODE_FMT_EXTENTS)
			xfs_attr_shortform_create(args);

		/*
		 * Try to add the attr to the attribute list in the inode.
		 */
		error = xfs_attr_try_sf_addname(dp, args);
		if (error != -ENOSPC)
			return error;

		/*
		 * It won't fit in the shortform, transform to a leaf block.
		 * GROT: another possible req'mt for a double-split btree op.
		 */
		error = xfs_attr_shortform_to_leaf(args, &leaf_bp);
		if (error)
			return error;

		/*
		 * Prevent the leaf buffer from being unlocked so that a
		 * concurrent AIL push cannot grab the half-baked leaf
		 * buffer and run into problems with the write verifier.
		 * Once we're done rolling the transaction we can release
		 * the hold and add the attr to the leaf.
		 */
		xfs_trans_bhold(args->trans, leaf_bp);
		error = xfs_defer_finish(&args->trans);
		xfs_trans_bhold_release(args->trans, leaf_bp);
		if (error) {
			xfs_trans_brelse(args->trans, leaf_bp);
			return error;
		}
	}

	if (xfs_bmap_one_block(dp, XFS_ATTR_FORK))
		error = xfs_attr_leaf_addname(args);
	else
		error = xfs_attr_node_addname(args);
	return error;
}