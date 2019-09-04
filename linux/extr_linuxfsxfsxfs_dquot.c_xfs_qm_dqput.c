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
struct xfs_quotainfo {int /*<<< orphan*/  qi_lru; } ;
struct xfs_dquot {scalar_t__ q_nrefs; TYPE_1__* q_mount; int /*<<< orphan*/  q_lru; } ;
struct TYPE_2__ {struct xfs_quotainfo* m_quotainfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_DQ_IS_LOCKED (struct xfs_dquot*) ; 
 int /*<<< orphan*/  XFS_STATS_INC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_dqput (struct xfs_dquot*) ; 
 int /*<<< orphan*/  trace_xfs_dqput_free (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dqunlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xs_qm_dquot_unused ; 

void
xfs_qm_dqput(
	struct xfs_dquot	*dqp)
{
	ASSERT(dqp->q_nrefs > 0);
	ASSERT(XFS_DQ_IS_LOCKED(dqp));

	trace_xfs_dqput(dqp);

	if (--dqp->q_nrefs == 0) {
		struct xfs_quotainfo	*qi = dqp->q_mount->m_quotainfo;
		trace_xfs_dqput_free(dqp);

		if (list_lru_add(&qi->qi_lru, &dqp->q_lru))
			XFS_STATS_INC(dqp->q_mount, xs_qm_dquot_unused);
	}
	xfs_dqunlock(dqp);
}