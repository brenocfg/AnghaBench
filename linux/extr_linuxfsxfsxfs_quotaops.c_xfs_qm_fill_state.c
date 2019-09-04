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
typedef  scalar_t__ xfs_ino_t ;
struct xfs_quotainfo {int /*<<< orphan*/  qi_rtbwarnlimit; int /*<<< orphan*/  qi_iwarnlimit; int /*<<< orphan*/  qi_bwarnlimit; int /*<<< orphan*/  qi_rtbtimelimit; int /*<<< orphan*/  qi_itimelimit; int /*<<< orphan*/  qi_btimelimit; } ;
struct xfs_mount {struct xfs_quotainfo* m_quotainfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  di_nextents; int /*<<< orphan*/  di_nblocks; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct qc_type_state {int /*<<< orphan*/  rt_spc_warnlimit; int /*<<< orphan*/  ino_warnlimit; int /*<<< orphan*/  spc_warnlimit; int /*<<< orphan*/  rt_spc_timelimit; int /*<<< orphan*/  ino_timelimit; int /*<<< orphan*/  spc_timelimit; int /*<<< orphan*/  nextents; int /*<<< orphan*/  blocks; int /*<<< orphan*/  flags; scalar_t__ ino; } ;

/* Variables and functions */
 scalar_t__ NULLFSINO ; 
 int /*<<< orphan*/  QCI_SYSFILE ; 
 scalar_t__ xfs_iget (struct xfs_mount*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_inode**) ; 
 int /*<<< orphan*/  xfs_irele (struct xfs_inode*) ; 

__attribute__((used)) static void
xfs_qm_fill_state(
	struct qc_type_state	*tstate,
	struct xfs_mount	*mp,
	struct xfs_inode	*ip,
	xfs_ino_t		ino)
{
	struct xfs_quotainfo *q = mp->m_quotainfo;
	bool tempqip = false;

	tstate->ino = ino;
	if (!ip && ino == NULLFSINO)
		return;
	if (!ip) {
		if (xfs_iget(mp, NULL, ino, 0, 0, &ip))
			return;
		tempqip = true;
	}
	tstate->flags |= QCI_SYSFILE;
	tstate->blocks = ip->i_d.di_nblocks;
	tstate->nextents = ip->i_d.di_nextents;
	tstate->spc_timelimit = q->qi_btimelimit;
	tstate->ino_timelimit = q->qi_itimelimit;
	tstate->rt_spc_timelimit = q->qi_rtbtimelimit;
	tstate->spc_warnlimit = q->qi_bwarnlimit;
	tstate->ino_warnlimit = q->qi_iwarnlimit;
	tstate->rt_spc_warnlimit = q->qi_rtbwarnlimit;
	if (tempqip)
		xfs_irele(ip);
}