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
struct xfs_mount {int /*<<< orphan*/  m_sb; struct xfs_dir_ops const* m_nondir_inode_ops; } ;
struct xfs_inode {struct xfs_dir_ops const* d_ops; } ;
struct xfs_dir_ops {int dummy; } ;

/* Variables and functions */
 struct xfs_dir_ops const xfs_dir2_nondir_ops ; 
 struct xfs_dir_ops const xfs_dir3_nondir_ops ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 

const struct xfs_dir_ops *
xfs_nondir_get_ops(
	struct xfs_mount	*mp,
	struct xfs_inode	*dp)
{
	if (dp)
		return dp->d_ops;
	if (mp->m_nondir_inode_ops)
		return mp->m_nondir_inode_ops;
	if (xfs_sb_version_hascrc(&mp->m_sb))
		return &xfs_dir3_nondir_ops;
	return &xfs_dir2_nondir_ops;
}