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
typedef  scalar_t__ uint ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {scalar_t__ d_flags; scalar_t__ d_id; int /*<<< orphan*/  d_rtbwarns; int /*<<< orphan*/  d_rtbtimer; int /*<<< orphan*/  d_rtb_softlimit; int /*<<< orphan*/  d_rtb_hardlimit; int /*<<< orphan*/  d_bwarns; int /*<<< orphan*/  d_iwarns; int /*<<< orphan*/  d_itimer; int /*<<< orphan*/  d_btimer; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; int /*<<< orphan*/  d_blk_softlimit; int /*<<< orphan*/  d_blk_hardlimit; } ;
struct xfs_dquot {void* q_res_bcount; scalar_t__ q_res_icount; void* q_res_rtbcount; TYPE_1__ q_core; } ;
struct qc_dqblk {scalar_t__ d_spc_softlimit; scalar_t__ d_ino_softlimit; scalar_t__ d_space; scalar_t__ d_ino_count; scalar_t__ d_spc_timer; scalar_t__ d_ino_timer; void* d_rt_spc_timer; void* d_rt_spc_warns; void* d_rt_space; void* d_rt_spc_softlimit; void* d_rt_spc_hardlimit; void* d_spc_warns; void* d_ino_warns; void* d_ino_hardlimit; void* d_spc_hardlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DQ_GROUP ; 
 scalar_t__ XFS_DQ_PROJ ; 
 scalar_t__ XFS_DQ_USER ; 
 void* XFS_FSB_TO_B (struct xfs_mount*,void*) ; 
 scalar_t__ XFS_IS_GQUOTA_ENFORCED (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_PQUOTA_ENFORCED (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_UQUOTA_ENFORCED (struct xfs_mount*) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qc_dqblk*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xfs_qm_scall_getquota_fill_qc(
	struct xfs_mount	*mp,
	uint			type,
	const struct xfs_dquot	*dqp,
	struct qc_dqblk		*dst)
{
	memset(dst, 0, sizeof(*dst));
	dst->d_spc_hardlimit =
		XFS_FSB_TO_B(mp, be64_to_cpu(dqp->q_core.d_blk_hardlimit));
	dst->d_spc_softlimit =
		XFS_FSB_TO_B(mp, be64_to_cpu(dqp->q_core.d_blk_softlimit));
	dst->d_ino_hardlimit = be64_to_cpu(dqp->q_core.d_ino_hardlimit);
	dst->d_ino_softlimit = be64_to_cpu(dqp->q_core.d_ino_softlimit);
	dst->d_space = XFS_FSB_TO_B(mp, dqp->q_res_bcount);
	dst->d_ino_count = dqp->q_res_icount;
	dst->d_spc_timer = be32_to_cpu(dqp->q_core.d_btimer);
	dst->d_ino_timer = be32_to_cpu(dqp->q_core.d_itimer);
	dst->d_ino_warns = be16_to_cpu(dqp->q_core.d_iwarns);
	dst->d_spc_warns = be16_to_cpu(dqp->q_core.d_bwarns);
	dst->d_rt_spc_hardlimit =
		XFS_FSB_TO_B(mp, be64_to_cpu(dqp->q_core.d_rtb_hardlimit));
	dst->d_rt_spc_softlimit =
		XFS_FSB_TO_B(mp, be64_to_cpu(dqp->q_core.d_rtb_softlimit));
	dst->d_rt_space = XFS_FSB_TO_B(mp, dqp->q_res_rtbcount);
	dst->d_rt_spc_timer = be32_to_cpu(dqp->q_core.d_rtbtimer);
	dst->d_rt_spc_warns = be16_to_cpu(dqp->q_core.d_rtbwarns);

	/*
	 * Internally, we don't reset all the timers when quota enforcement
	 * gets turned off. No need to confuse the user level code,
	 * so return zeroes in that case.
	 */
	if ((!XFS_IS_UQUOTA_ENFORCED(mp) &&
	     dqp->q_core.d_flags == XFS_DQ_USER) ||
	    (!XFS_IS_GQUOTA_ENFORCED(mp) &&
	     dqp->q_core.d_flags == XFS_DQ_GROUP) ||
	    (!XFS_IS_PQUOTA_ENFORCED(mp) &&
	     dqp->q_core.d_flags == XFS_DQ_PROJ)) {
		dst->d_spc_timer = 0;
		dst->d_ino_timer = 0;
		dst->d_rt_spc_timer = 0;
	}

#ifdef DEBUG
	if (((XFS_IS_UQUOTA_ENFORCED(mp) && type == XFS_DQ_USER) ||
	     (XFS_IS_GQUOTA_ENFORCED(mp) && type == XFS_DQ_GROUP) ||
	     (XFS_IS_PQUOTA_ENFORCED(mp) && type == XFS_DQ_PROJ)) &&
	    dqp->q_core.d_id != 0) {
		if ((dst->d_space > dst->d_spc_softlimit) &&
		    (dst->d_spc_softlimit > 0)) {
			ASSERT(dst->d_spc_timer != 0);
		}
		if ((dst->d_ino_count > dst->d_ino_softlimit) &&
		    (dst->d_ino_softlimit > 0)) {
			ASSERT(dst->d_ino_timer != 0);
		}
	}
#endif
}