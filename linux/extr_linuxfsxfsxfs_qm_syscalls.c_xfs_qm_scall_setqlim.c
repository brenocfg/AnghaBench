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
typedef  scalar_t__ xfs_qcnt_t ;
typedef  scalar_t__ xfs_dqid_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_trans {int dummy; } ;
struct xfs_quotainfo {int /*<<< orphan*/  qi_quotaofflock; int /*<<< orphan*/  qi_rtbwarnlimit; int /*<<< orphan*/  qi_iwarnlimit; int /*<<< orphan*/  qi_bwarnlimit; int /*<<< orphan*/  qi_rtbtimelimit; int /*<<< orphan*/  qi_itimelimit; int /*<<< orphan*/  qi_btimelimit; } ;
struct xfs_mount {struct xfs_quotainfo* m_quotainfo; } ;
struct xfs_disk_dquot {void* d_rtbtimer; void* d_itimer; void* d_btimer; void* d_rtbwarns; void* d_iwarns; void* d_bwarns; void* d_ino_softlimit; void* d_ino_hardlimit; void* d_rtb_softlimit; void* d_rtb_hardlimit; void* d_blk_softlimit; void* d_blk_hardlimit; } ;
struct xfs_dquot {int /*<<< orphan*/  dq_flags; struct xfs_disk_dquot q_core; } ;
struct xfs_def_quota {scalar_t__ isoftlimit; scalar_t__ ihardlimit; scalar_t__ rtbsoftlimit; scalar_t__ rtbhardlimit; scalar_t__ bsoftlimit; scalar_t__ bhardlimit; } ;
struct qc_dqblk {int d_fieldmask; int /*<<< orphan*/  d_rt_spc_warns; int /*<<< orphan*/  d_ino_warns; int /*<<< orphan*/  d_spc_warns; int /*<<< orphan*/  d_rt_spc_timer; int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_spc_timer; scalar_t__ d_ino_softlimit; scalar_t__ d_ino_hardlimit; int /*<<< orphan*/  d_rt_spc_softlimit; int /*<<< orphan*/  d_rt_spc_hardlimit; int /*<<< orphan*/  d_spc_softlimit; int /*<<< orphan*/  d_spc_hardlimit; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_qm_setqlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int QC_INO_HARD ; 
 int QC_INO_SOFT ; 
 int QC_INO_TIMER ; 
 int QC_INO_WARNS ; 
 int QC_RT_SPC_HARD ; 
 int QC_RT_SPC_SOFT ; 
 int QC_RT_SPC_TIMER ; 
 int QC_RT_SPC_WARNS ; 
 int QC_SPC_HARD ; 
 int QC_SPC_SOFT ; 
 int QC_SPC_TIMER ; 
 int QC_SPC_WARNS ; 
 scalar_t__ XFS_B_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DQ_DIRTY ; 
 int XFS_QC_MASK ; 
 scalar_t__ be64_to_cpu (void*) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_debug (struct xfs_mount*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dqlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dqunlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dquot_set_prealloc_limits (struct xfs_dquot*) ; 
 struct xfs_def_quota* xfs_get_defquota (struct xfs_dquot*,struct xfs_quotainfo*) ; 
 int /*<<< orphan*/  xfs_qm_adjust_dqtimers (struct xfs_mount*,struct xfs_disk_dquot*) ; 
 int xfs_qm_dqget (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ,int,struct xfs_dquot**) ; 
 int /*<<< orphan*/  xfs_qm_dqrele (struct xfs_dquot*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_dqjoin (struct xfs_trans*,struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_trans_log_dquot (struct xfs_trans*,struct xfs_dquot*) ; 

int
xfs_qm_scall_setqlim(
	struct xfs_mount	*mp,
	xfs_dqid_t		id,
	uint			type,
	struct qc_dqblk		*newlim)
{
	struct xfs_quotainfo	*q = mp->m_quotainfo;
	struct xfs_disk_dquot	*ddq;
	struct xfs_dquot	*dqp;
	struct xfs_trans	*tp;
	struct xfs_def_quota	*defq;
	int			error;
	xfs_qcnt_t		hard, soft;

	if (newlim->d_fieldmask & ~XFS_QC_MASK)
		return -EINVAL;
	if ((newlim->d_fieldmask & XFS_QC_MASK) == 0)
		return 0;

	/*
	 * We don't want to race with a quotaoff so take the quotaoff lock.
	 * We don't hold an inode lock, so there's nothing else to stop
	 * a quotaoff from happening.
	 */
	mutex_lock(&q->qi_quotaofflock);

	/*
	 * Get the dquot (locked) before we start, as we need to do a
	 * transaction to allocate it if it doesn't exist. Once we have the
	 * dquot, unlock it so we can start the next transaction safely. We hold
	 * a reference to the dquot, so it's safe to do this unlock/lock without
	 * it being reclaimed in the mean time.
	 */
	error = xfs_qm_dqget(mp, id, type, true, &dqp);
	if (error) {
		ASSERT(error != -ENOENT);
		goto out_unlock;
	}

	defq = xfs_get_defquota(dqp, q);
	xfs_dqunlock(dqp);

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_qm_setqlim, 0, 0, 0, &tp);
	if (error)
		goto out_rele;

	xfs_dqlock(dqp);
	xfs_trans_dqjoin(tp, dqp);
	ddq = &dqp->q_core;

	/*
	 * Make sure that hardlimits are >= soft limits before changing.
	 */
	hard = (newlim->d_fieldmask & QC_SPC_HARD) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_spc_hardlimit) :
			be64_to_cpu(ddq->d_blk_hardlimit);
	soft = (newlim->d_fieldmask & QC_SPC_SOFT) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_spc_softlimit) :
			be64_to_cpu(ddq->d_blk_softlimit);
	if (hard == 0 || hard >= soft) {
		ddq->d_blk_hardlimit = cpu_to_be64(hard);
		ddq->d_blk_softlimit = cpu_to_be64(soft);
		xfs_dquot_set_prealloc_limits(dqp);
		if (id == 0) {
			defq->bhardlimit = hard;
			defq->bsoftlimit = soft;
		}
	} else {
		xfs_debug(mp, "blkhard %Ld < blksoft %Ld", hard, soft);
	}
	hard = (newlim->d_fieldmask & QC_RT_SPC_HARD) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_rt_spc_hardlimit) :
			be64_to_cpu(ddq->d_rtb_hardlimit);
	soft = (newlim->d_fieldmask & QC_RT_SPC_SOFT) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_rt_spc_softlimit) :
			be64_to_cpu(ddq->d_rtb_softlimit);
	if (hard == 0 || hard >= soft) {
		ddq->d_rtb_hardlimit = cpu_to_be64(hard);
		ddq->d_rtb_softlimit = cpu_to_be64(soft);
		if (id == 0) {
			defq->rtbhardlimit = hard;
			defq->rtbsoftlimit = soft;
		}
	} else {
		xfs_debug(mp, "rtbhard %Ld < rtbsoft %Ld", hard, soft);
	}

	hard = (newlim->d_fieldmask & QC_INO_HARD) ?
		(xfs_qcnt_t) newlim->d_ino_hardlimit :
			be64_to_cpu(ddq->d_ino_hardlimit);
	soft = (newlim->d_fieldmask & QC_INO_SOFT) ?
		(xfs_qcnt_t) newlim->d_ino_softlimit :
			be64_to_cpu(ddq->d_ino_softlimit);
	if (hard == 0 || hard >= soft) {
		ddq->d_ino_hardlimit = cpu_to_be64(hard);
		ddq->d_ino_softlimit = cpu_to_be64(soft);
		if (id == 0) {
			defq->ihardlimit = hard;
			defq->isoftlimit = soft;
		}
	} else {
		xfs_debug(mp, "ihard %Ld < isoft %Ld", hard, soft);
	}

	/*
	 * Update warnings counter(s) if requested
	 */
	if (newlim->d_fieldmask & QC_SPC_WARNS)
		ddq->d_bwarns = cpu_to_be16(newlim->d_spc_warns);
	if (newlim->d_fieldmask & QC_INO_WARNS)
		ddq->d_iwarns = cpu_to_be16(newlim->d_ino_warns);
	if (newlim->d_fieldmask & QC_RT_SPC_WARNS)
		ddq->d_rtbwarns = cpu_to_be16(newlim->d_rt_spc_warns);

	if (id == 0) {
		/*
		 * Timelimits for the super user set the relative time
		 * the other users can be over quota for this file system.
		 * If it is zero a default is used.  Ditto for the default
		 * soft and hard limit values (already done, above), and
		 * for warnings.
		 */
		if (newlim->d_fieldmask & QC_SPC_TIMER) {
			q->qi_btimelimit = newlim->d_spc_timer;
			ddq->d_btimer = cpu_to_be32(newlim->d_spc_timer);
		}
		if (newlim->d_fieldmask & QC_INO_TIMER) {
			q->qi_itimelimit = newlim->d_ino_timer;
			ddq->d_itimer = cpu_to_be32(newlim->d_ino_timer);
		}
		if (newlim->d_fieldmask & QC_RT_SPC_TIMER) {
			q->qi_rtbtimelimit = newlim->d_rt_spc_timer;
			ddq->d_rtbtimer = cpu_to_be32(newlim->d_rt_spc_timer);
		}
		if (newlim->d_fieldmask & QC_SPC_WARNS)
			q->qi_bwarnlimit = newlim->d_spc_warns;
		if (newlim->d_fieldmask & QC_INO_WARNS)
			q->qi_iwarnlimit = newlim->d_ino_warns;
		if (newlim->d_fieldmask & QC_RT_SPC_WARNS)
			q->qi_rtbwarnlimit = newlim->d_rt_spc_warns;
	} else {
		/*
		 * If the user is now over quota, start the timelimit.
		 * The user will not be 'warned'.
		 * Note that we keep the timers ticking, whether enforcement
		 * is on or off. We don't really want to bother with iterating
		 * over all ondisk dquots and turning the timers on/off.
		 */
		xfs_qm_adjust_dqtimers(mp, ddq);
	}
	dqp->dq_flags |= XFS_DQ_DIRTY;
	xfs_trans_log_dquot(tp, dqp);

	error = xfs_trans_commit(tp);

out_rele:
	xfs_qm_dqrele(dqp);
out_unlock:
	mutex_unlock(&q->qi_quotaofflock);
	return error;
}