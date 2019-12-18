#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sb_dblocks; scalar_t__ sb_fdblocks; scalar_t__ sb_icount; scalar_t__ sb_ifree; } ;
typedef  TYPE_1__ xfs_sb_t ;
struct TYPE_6__ {scalar_t__ pagi_freecount; scalar_t__ pagi_count; scalar_t__ pagf_freeblks; scalar_t__ pagf_flcount; scalar_t__ pagf_btreeblks; } ;
typedef  TYPE_2__ xfs_perag_t ;
typedef  scalar_t__ xfs_agnumber_t ;
typedef  scalar_t__ uint64_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_SICK_FS_COUNTERS ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_alert (struct xfs_mount*,char*) ; 
 int xfs_alloc_pagf_init (struct xfs_mount*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_fs_mark_healthy (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_ialloc_pagi_init (struct xfs_mount*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* xfs_perag_get (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_reinit_percpu_counters (struct xfs_mount*) ; 

int
xfs_initialize_perag_data(
	struct xfs_mount *mp,
	xfs_agnumber_t	agcount)
{
	xfs_agnumber_t	index;
	xfs_perag_t	*pag;
	xfs_sb_t	*sbp = &mp->m_sb;
	uint64_t	ifree = 0;
	uint64_t	ialloc = 0;
	uint64_t	bfree = 0;
	uint64_t	bfreelst = 0;
	uint64_t	btree = 0;
	uint64_t	fdblocks;
	int		error = 0;

	for (index = 0; index < agcount; index++) {
		/*
		 * read the agf, then the agi. This gets us
		 * all the information we need and populates the
		 * per-ag structures for us.
		 */
		error = xfs_alloc_pagf_init(mp, NULL, index, 0);
		if (error)
			return error;

		error = xfs_ialloc_pagi_init(mp, NULL, index);
		if (error)
			return error;
		pag = xfs_perag_get(mp, index);
		ifree += pag->pagi_freecount;
		ialloc += pag->pagi_count;
		bfree += pag->pagf_freeblks;
		bfreelst += pag->pagf_flcount;
		btree += pag->pagf_btreeblks;
		xfs_perag_put(pag);
	}
	fdblocks = bfree + bfreelst + btree;

	/*
	 * If the new summary counts are obviously incorrect, fail the
	 * mount operation because that implies the AGFs are also corrupt.
	 * Clear FS_COUNTERS so that we don't unmount with a dirty log, which
	 * will prevent xfs_repair from fixing anything.
	 */
	if (fdblocks > sbp->sb_dblocks || ifree > ialloc) {
		xfs_alert(mp, "AGF corruption. Please run xfs_repair.");
		error = -EFSCORRUPTED;
		goto out;
	}

	/* Overwrite incore superblock counters with just-read data */
	spin_lock(&mp->m_sb_lock);
	sbp->sb_ifree = ifree;
	sbp->sb_icount = ialloc;
	sbp->sb_fdblocks = fdblocks;
	spin_unlock(&mp->m_sb_lock);

	xfs_reinit_percpu_counters(mp);
out:
	xfs_fs_mark_healthy(mp, XFS_SICK_FS_COUNTERS);
	return error;
}