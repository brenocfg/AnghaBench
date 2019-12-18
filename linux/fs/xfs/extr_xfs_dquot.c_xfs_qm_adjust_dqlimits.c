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
struct xfs_quotainfo {int dummy; } ;
struct xfs_mount {struct xfs_quotainfo* m_quotainfo; } ;
struct xfs_disk_dquot {void* d_rtb_hardlimit; void* d_rtb_softlimit; void* d_ino_hardlimit; void* d_ino_softlimit; void* d_blk_hardlimit; void* d_blk_softlimit; int /*<<< orphan*/  d_id; } ;
struct xfs_dquot {struct xfs_disk_dquot q_core; } ;
struct xfs_def_quota {scalar_t__ rtbhardlimit; scalar_t__ rtbsoftlimit; scalar_t__ ihardlimit; scalar_t__ isoftlimit; scalar_t__ bhardlimit; scalar_t__ bsoftlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  xfs_dquot_set_prealloc_limits (struct xfs_dquot*) ; 
 struct xfs_def_quota* xfs_get_defquota (struct xfs_dquot*,struct xfs_quotainfo*) ; 

void
xfs_qm_adjust_dqlimits(
	struct xfs_mount	*mp,
	struct xfs_dquot	*dq)
{
	struct xfs_quotainfo	*q = mp->m_quotainfo;
	struct xfs_disk_dquot	*d = &dq->q_core;
	struct xfs_def_quota	*defq;
	int			prealloc = 0;

	ASSERT(d->d_id);
	defq = xfs_get_defquota(dq, q);

	if (defq->bsoftlimit && !d->d_blk_softlimit) {
		d->d_blk_softlimit = cpu_to_be64(defq->bsoftlimit);
		prealloc = 1;
	}
	if (defq->bhardlimit && !d->d_blk_hardlimit) {
		d->d_blk_hardlimit = cpu_to_be64(defq->bhardlimit);
		prealloc = 1;
	}
	if (defq->isoftlimit && !d->d_ino_softlimit)
		d->d_ino_softlimit = cpu_to_be64(defq->isoftlimit);
	if (defq->ihardlimit && !d->d_ino_hardlimit)
		d->d_ino_hardlimit = cpu_to_be64(defq->ihardlimit);
	if (defq->rtbsoftlimit && !d->d_rtb_softlimit)
		d->d_rtb_softlimit = cpu_to_be64(defq->rtbsoftlimit);
	if (defq->rtbhardlimit && !d->d_rtb_hardlimit)
		d->d_rtb_hardlimit = cpu_to_be64(defq->rtbhardlimit);

	if (prealloc)
		xfs_dquot_set_prealloc_limits(dq);
}