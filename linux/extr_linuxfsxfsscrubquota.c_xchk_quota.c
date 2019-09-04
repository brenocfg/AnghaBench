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
typedef  int /*<<< orphan*/  uint ;
struct xfs_scrub {scalar_t__ ilock_flags; int /*<<< orphan*/  ip; TYPE_1__* sm; struct xfs_mount* mp; } ;
struct xfs_quotainfo {int qi_dqperchunk; } ;
struct xfs_mount {struct xfs_quotainfo* m_quotainfo; } ;
struct xchk_quota_info {int last_id; struct xfs_scrub* sc; } ;
struct TYPE_2__ {int sm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_ILOCK_EXCL ; 
 int XFS_SCRUB_OFLAG_CORRUPT ; 
 int /*<<< orphan*/  xchk_fblock_process_error (struct xfs_scrub*,int /*<<< orphan*/ ,int,int*) ; 
 int xchk_quota_data_fork (struct xfs_scrub*) ; 
 int /*<<< orphan*/  xchk_quota_item ; 
 int /*<<< orphan*/  xchk_quota_to_dqtype (struct xfs_scrub*) ; 
 int /*<<< orphan*/  xfs_ilock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_iunlock (int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_qm_dqiterate (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xchk_quota_info*) ; 

int
xchk_quota(
	struct xfs_scrub	*sc)
{
	struct xchk_quota_info	sqi;
	struct xfs_mount	*mp = sc->mp;
	struct xfs_quotainfo	*qi = mp->m_quotainfo;
	uint			dqtype;
	int			error = 0;

	dqtype = xchk_quota_to_dqtype(sc);

	/* Look for problem extents. */
	error = xchk_quota_data_fork(sc);
	if (error)
		goto out;
	if (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		goto out;

	/*
	 * Check all the quota items.  Now that we've checked the quota inode
	 * data fork we have to drop ILOCK_EXCL to use the regular dquot
	 * functions.
	 */
	xfs_iunlock(sc->ip, sc->ilock_flags);
	sc->ilock_flags = 0;
	sqi.sc = sc;
	sqi.last_id = 0;
	error = xfs_qm_dqiterate(mp, dqtype, xchk_quota_item, &sqi);
	sc->ilock_flags = XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);
	if (!xchk_fblock_process_error(sc, XFS_DATA_FORK,
			sqi.last_id * qi->qi_dqperchunk, &error))
		goto out;

out:
	return error;
}