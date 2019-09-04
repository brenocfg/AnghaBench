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
struct TYPE_2__ {scalar_t__ di_aformat; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct xfs_attr_list_context {struct xfs_inode* dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int XFS_ILOCK_EXCL ; 
 int XFS_ILOCK_SHARED ; 
 int xfs_attr_leaf_list (struct xfs_attr_list_context*) ; 
 int xfs_attr_node_list (struct xfs_attr_list_context*) ; 
 int xfs_attr_shortform_list (struct xfs_attr_list_context*) ; 
 scalar_t__ xfs_bmap_one_block (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_hasattr (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_isilocked (struct xfs_inode*,int) ; 

int
xfs_attr_list_int_ilocked(
	struct xfs_attr_list_context	*context)
{
	struct xfs_inode		*dp = context->dp;

	ASSERT(xfs_isilocked(dp, XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));

	/*
	 * Decide on what work routines to call based on the inode size.
	 */
	if (!xfs_inode_hasattr(dp))
		return 0;
	else if (dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL)
		return xfs_attr_shortform_list(context);
	else if (xfs_bmap_one_block(dp, XFS_ATTR_FORK))
		return xfs_attr_leaf_list(context);
	return xfs_attr_node_list(context);
}