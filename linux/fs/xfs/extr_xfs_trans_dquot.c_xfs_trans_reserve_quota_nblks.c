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
typedef  int uint ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_inode {int /*<<< orphan*/  i_pdquot; int /*<<< orphan*/  i_gdquot; int /*<<< orphan*/  i_udquot; int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 scalar_t__ XFS_IS_PQUOTA_ON (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (struct xfs_mount*) ; 
 int XFS_QMOPT_ENOSPC ; 
 int XFS_QMOPT_FORCE_RES ; 
 int XFS_TRANS_DQ_RES_BLKS ; 
 int XFS_TRANS_DQ_RES_RTBLKS ; 
 int /*<<< orphan*/  xfs_is_quota_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_isilocked (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve_quota_bydquots (struct xfs_trans*,struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int) ; 

int
xfs_trans_reserve_quota_nblks(
	struct xfs_trans	*tp,
	struct xfs_inode	*ip,
	int64_t			nblks,
	long			ninos,
	uint			flags)
{
	struct xfs_mount	*mp = ip->i_mount;

	if (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		return 0;
	if (XFS_IS_PQUOTA_ON(mp))
		flags |= XFS_QMOPT_ENOSPC;

	ASSERT(!xfs_is_quota_inode(&mp->m_sb, ip->i_ino));

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT((flags & ~(XFS_QMOPT_FORCE_RES | XFS_QMOPT_ENOSPC)) ==
				XFS_TRANS_DQ_RES_RTBLKS ||
	       (flags & ~(XFS_QMOPT_FORCE_RES | XFS_QMOPT_ENOSPC)) ==
				XFS_TRANS_DQ_RES_BLKS);

	/*
	 * Reserve nblks against these dquots, with trans as the mediator.
	 */
	return xfs_trans_reserve_quota_bydquots(tp, mp,
						ip->i_udquot, ip->i_gdquot,
						ip->i_pdquot,
						nblks, ninos, flags);
}