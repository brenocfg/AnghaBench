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
struct TYPE_3__ {scalar_t__ di_aformat; } ;
struct xfs_inode {TYPE_2__* i_afp; TYPE_1__ i_d; } ;
struct xfs_da_args {struct xfs_inode* dp; } ;
struct TYPE_4__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOATTR ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int XFS_IFINLINE ; 
 int xfs_attr_leaf_removename (struct xfs_da_args*) ; 
 int xfs_attr_node_removename (struct xfs_da_args*) ; 
 int xfs_attr_shortform_remove (struct xfs_da_args*) ; 
 scalar_t__ xfs_bmap_one_block (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_hasattr (struct xfs_inode*) ; 

int
xfs_attr_remove_args(
	struct xfs_da_args      *args)
{
	struct xfs_inode	*dp = args->dp;
	int			error;

	if (!xfs_inode_hasattr(dp)) {
		error = -ENOATTR;
	} else if (dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL) {
		ASSERT(dp->i_afp->if_flags & XFS_IFINLINE);
		error = xfs_attr_shortform_remove(args);
	} else if (xfs_bmap_one_block(dp, XFS_ATTR_FORK)) {
		error = xfs_attr_leaf_removename(args);
	} else {
		error = xfs_attr_node_removename(args);
	}

	return error;
}