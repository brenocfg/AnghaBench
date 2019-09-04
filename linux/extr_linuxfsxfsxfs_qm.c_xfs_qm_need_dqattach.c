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
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_NOT_DQATTACHED (struct xfs_mount*,struct xfs_inode*) ; 
 scalar_t__ xfs_is_quota_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
xfs_qm_need_dqattach(
	struct xfs_inode	*ip)
{
	struct xfs_mount	*mp = ip->i_mount;

	if (!XFS_IS_QUOTA_RUNNING(mp))
		return false;
	if (!XFS_IS_QUOTA_ON(mp))
		return false;
	if (!XFS_NOT_DQATTACHED(mp, ip))
		return false;
	if (xfs_is_quota_inode(&mp->m_sb, ip->i_ino))
		return false;
	return true;
}