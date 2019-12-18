#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
struct xfs_scrub {int /*<<< orphan*/  ilock_flags; int /*<<< orphan*/  ip; TYPE_2__* mp; int /*<<< orphan*/  flags; } ;
struct xfs_inode {int dummy; } ;
struct TYPE_7__ {TYPE_1__* m_quotainfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  qi_quotaofflock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  XCHK_HAS_QUOTAOFFLOCK ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (TYPE_2__*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ xchk_quota_to_dqtype (struct xfs_scrub*) ; 
 int xchk_setup_fs (struct xfs_scrub*,struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_ilock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_quota_inode (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_this_quota_on (TYPE_2__*,scalar_t__) ; 

int
xchk_setup_quota(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	uint			dqtype;
	int			error;

	if (!XFS_IS_QUOTA_RUNNING(sc->mp) || !XFS_IS_QUOTA_ON(sc->mp))
		return -ENOENT;

	dqtype = xchk_quota_to_dqtype(sc);
	if (dqtype == 0)
		return -EINVAL;
	sc->flags |= XCHK_HAS_QUOTAOFFLOCK;
	mutex_lock(&sc->mp->m_quotainfo->qi_quotaofflock);
	if (!xfs_this_quota_on(sc->mp, dqtype))
		return -ENOENT;
	error = xchk_setup_fs(sc, ip);
	if (error)
		return error;
	sc->ip = xfs_quota_inode(sc->mp, dqtype);
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);
	sc->ilock_flags = XFS_ILOCK_EXCL;
	return 0;
}