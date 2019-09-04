#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int if_flags; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_sb; TYPE_1__* i_mapping; } ;
struct xfs_inode {TYPE_2__ i_df; struct inode i_vnode; } ;
struct TYPE_6__ {int /*<<< orphan*/  m_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DAX (struct inode*) ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int XFS_IFINLINE ; 
 TYPE_3__* XFS_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_address_space_operations ; 
 int /*<<< orphan*/  xfs_dax_aops ; 
 int /*<<< orphan*/  xfs_dir_ci_inode_operations ; 
 int /*<<< orphan*/  xfs_dir_file_operations ; 
 int /*<<< orphan*/  xfs_dir_inode_operations ; 
 int /*<<< orphan*/  xfs_file_operations ; 
 int /*<<< orphan*/  xfs_inline_symlink_inode_operations ; 
 int /*<<< orphan*/  xfs_inode_operations ; 
 int /*<<< orphan*/  xfs_sb_version_hasasciici (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_symlink_inode_operations ; 

void
xfs_setup_iops(
	struct xfs_inode	*ip)
{
	struct inode		*inode = &ip->i_vnode;

	switch (inode->i_mode & S_IFMT) {
	case S_IFREG:
		inode->i_op = &xfs_inode_operations;
		inode->i_fop = &xfs_file_operations;
		if (IS_DAX(inode))
			inode->i_mapping->a_ops = &xfs_dax_aops;
		else
			inode->i_mapping->a_ops = &xfs_address_space_operations;
		break;
	case S_IFDIR:
		if (xfs_sb_version_hasasciici(&XFS_M(inode->i_sb)->m_sb))
			inode->i_op = &xfs_dir_ci_inode_operations;
		else
			inode->i_op = &xfs_dir_inode_operations;
		inode->i_fop = &xfs_dir_file_operations;
		break;
	case S_IFLNK:
		if (ip->i_df.if_flags & XFS_IFINLINE)
			inode->i_op = &xfs_inline_symlink_inode_operations;
		else
			inode->i_op = &xfs_symlink_inode_operations;
		break;
	default:
		inode->i_op = &xfs_inode_operations;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		break;
	}
}