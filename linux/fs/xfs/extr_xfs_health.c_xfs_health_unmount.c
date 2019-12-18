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
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_perag {int dummy; } ;
struct TYPE_2__ {scalar_t__ sb_agcount; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 unsigned int XFS_SICK_FS_COUNTERS ; 
 int /*<<< orphan*/  trace_xfs_ag_unfixed_corruption (struct xfs_mount*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  trace_xfs_fs_unfixed_corruption (struct xfs_mount*,unsigned int) ; 
 int /*<<< orphan*/  trace_xfs_rt_unfixed_corruption (struct xfs_mount*,unsigned int) ; 
 int /*<<< orphan*/  xfs_ag_measure_sickness (struct xfs_perag*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  xfs_fs_mark_healthy (struct xfs_mount*,unsigned int) ; 
 int /*<<< orphan*/  xfs_fs_measure_sickness (struct xfs_mount*,unsigned int*,unsigned int*) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int /*<<< orphan*/  xfs_rt_measure_sickness (struct xfs_mount*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*) ; 

void
xfs_health_unmount(
	struct xfs_mount	*mp)
{
	struct xfs_perag	*pag;
	xfs_agnumber_t		agno;
	unsigned int		sick = 0;
	unsigned int		checked = 0;
	bool			warn = false;

	if (XFS_FORCED_SHUTDOWN(mp))
		return;

	/* Measure AG corruption levels. */
	for (agno = 0; agno < mp->m_sb.sb_agcount; agno++) {
		pag = xfs_perag_get(mp, agno);
		xfs_ag_measure_sickness(pag, &sick, &checked);
		if (sick) {
			trace_xfs_ag_unfixed_corruption(mp, agno, sick);
			warn = true;
		}
		xfs_perag_put(pag);
	}

	/* Measure realtime volume corruption levels. */
	xfs_rt_measure_sickness(mp, &sick, &checked);
	if (sick) {
		trace_xfs_rt_unfixed_corruption(mp, sick);
		warn = true;
	}

	/*
	 * Measure fs corruption and keep the sample around for the warning.
	 * See the note below for why we exempt FS_COUNTERS.
	 */
	xfs_fs_measure_sickness(mp, &sick, &checked);
	if (sick & ~XFS_SICK_FS_COUNTERS) {
		trace_xfs_fs_unfixed_corruption(mp, sick);
		warn = true;
	}

	if (warn) {
		xfs_warn(mp,
"Uncorrected metadata errors detected; please run xfs_repair.");

		/*
		 * We discovered uncorrected metadata problems at some point
		 * during this filesystem mount and have advised the
		 * administrator to run repair once the unmount completes.
		 *
		 * However, we must be careful -- when FSCOUNTERS are flagged
		 * unhealthy, the unmount procedure omits writing the clean
		 * unmount record to the log so that the next mount will run
		 * recovery and recompute the summary counters.  In other
		 * words, we leave a dirty log to get the counters fixed.
		 *
		 * Unfortunately, xfs_repair cannot recover dirty logs, so if
		 * there were filesystem problems, FSCOUNTERS was flagged, and
		 * the administrator takes our advice to run xfs_repair,
		 * they'll have to zap the log before repairing structures.
		 * We don't really want to encourage this, so we mark the
		 * FSCOUNTERS healthy so that a subsequent repair run won't see
		 * a dirty log.
		 */
		if (sick & XFS_SICK_FS_COUNTERS)
			xfs_fs_mark_healthy(mp, XFS_SICK_FS_COUNTERS);
	}
}