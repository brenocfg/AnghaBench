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
struct xfs_scrub {TYPE_2__* sm; struct xchk_fscounters* buf; struct xfs_mount* mp; } ;
struct TYPE_3__ {scalar_t__ sb_dblocks; } ;
struct xfs_mount {int /*<<< orphan*/  m_fdblocks; int /*<<< orphan*/  m_ifree; int /*<<< orphan*/  m_icount; TYPE_1__ m_sb; } ;
struct xchk_fscounters {scalar_t__ icount_min; scalar_t__ icount_max; int /*<<< orphan*/  fdblocks; int /*<<< orphan*/  ifree; int /*<<< orphan*/  icount; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int sm_flags; } ;

/* Variables and functions */
 scalar_t__ XCHK_FSCOUNT_MIN_VARIANCE ; 
 int /*<<< orphan*/  XFS_SB_BLOCK (struct xfs_mount*) ; 
 int XFS_SCRUB_OFLAG_INCOMPLETE ; 
 scalar_t__ percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int xchk_fscount_aggregate_agcounts (struct xfs_scrub*,struct xchk_fscounters*) ; 
 int /*<<< orphan*/  xchk_fscount_within_range (struct xfs_scrub*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_process_error (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xchk_set_corrupt (struct xfs_scrub*) ; 

int
xchk_fscounters(
	struct xfs_scrub	*sc)
{
	struct xfs_mount	*mp = sc->mp;
	struct xchk_fscounters	*fsc = sc->buf;
	int64_t			icount, ifree, fdblocks;
	int			error;

	/* Snapshot the percpu counters. */
	icount = percpu_counter_sum(&mp->m_icount);
	ifree = percpu_counter_sum(&mp->m_ifree);
	fdblocks = percpu_counter_sum(&mp->m_fdblocks);

	/* No negative values, please! */
	if (icount < 0 || ifree < 0 || fdblocks < 0)
		xchk_set_corrupt(sc);

	/* See if icount is obviously wrong. */
	if (icount < fsc->icount_min || icount > fsc->icount_max)
		xchk_set_corrupt(sc);

	/* See if fdblocks is obviously wrong. */
	if (fdblocks > mp->m_sb.sb_dblocks)
		xchk_set_corrupt(sc);

	/*
	 * If ifree exceeds icount by more than the minimum variance then
	 * something's probably wrong with the counters.
	 */
	if (ifree > icount && ifree - icount > XCHK_FSCOUNT_MIN_VARIANCE)
		xchk_set_corrupt(sc);

	/* Walk the incore AG headers to calculate the expected counters. */
	error = xchk_fscount_aggregate_agcounts(sc, fsc);
	if (!xchk_process_error(sc, 0, XFS_SB_BLOCK(mp), &error))
		return error;
	if (sc->sm->sm_flags & XFS_SCRUB_OFLAG_INCOMPLETE)
		return 0;

	/* Compare the in-core counters with whatever we counted. */
	if (!xchk_fscount_within_range(sc, icount, &mp->m_icount, fsc->icount))
		xchk_set_corrupt(sc);

	if (!xchk_fscount_within_range(sc, ifree, &mp->m_ifree, fsc->ifree))
		xchk_set_corrupt(sc);

	if (!xchk_fscount_within_range(sc, fdblocks, &mp->m_fdblocks,
			fsc->fdblocks))
		xchk_set_corrupt(sc);

	return 0;
}