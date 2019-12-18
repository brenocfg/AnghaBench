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
struct xfs_quotainfo {int /*<<< orphan*/  qi_pquotaip; int /*<<< orphan*/  qi_gquotaip; int /*<<< orphan*/  qi_uquotaip; int /*<<< orphan*/  qi_dquots; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_pquotino; int /*<<< orphan*/  sb_gquotino; int /*<<< orphan*/  sb_uquotino; } ;
struct xfs_mount {TYPE_1__ m_sb; struct xfs_quotainfo* m_quotainfo; } ;
struct super_block {int dummy; } ;
struct qc_state {TYPE_2__* s_state; int /*<<< orphan*/  s_incoredqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t GRPQUOTA ; 
 size_t PRJQUOTA ; 
 int /*<<< orphan*/  QCI_ACCT_ENABLED ; 
 int /*<<< orphan*/  QCI_LIMITS_ENFORCED ; 
 size_t USRQUOTA ; 
 scalar_t__ XFS_IS_GQUOTA_ENFORCED (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_GQUOTA_RUNNING (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_PQUOTA_ENFORCED (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_PQUOTA_RUNNING (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_UQUOTA_ENFORCED (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_UQUOTA_RUNNING (struct xfs_mount*) ; 
 struct xfs_mount* XFS_M (struct super_block*) ; 
 int /*<<< orphan*/  memset (struct qc_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_qm_fill_state (TYPE_2__*,struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_fs_get_quota_state(
	struct super_block	*sb,
	struct qc_state		*state)
{
	struct xfs_mount *mp = XFS_M(sb);
	struct xfs_quotainfo *q = mp->m_quotainfo;

	memset(state, 0, sizeof(*state));
	if (!XFS_IS_QUOTA_RUNNING(mp))
		return 0;
	state->s_incoredqs = q->qi_dquots;
	if (XFS_IS_UQUOTA_RUNNING(mp))
		state->s_state[USRQUOTA].flags |= QCI_ACCT_ENABLED;
	if (XFS_IS_UQUOTA_ENFORCED(mp))
		state->s_state[USRQUOTA].flags |= QCI_LIMITS_ENFORCED;
	if (XFS_IS_GQUOTA_RUNNING(mp))
		state->s_state[GRPQUOTA].flags |= QCI_ACCT_ENABLED;
	if (XFS_IS_GQUOTA_ENFORCED(mp))
		state->s_state[GRPQUOTA].flags |= QCI_LIMITS_ENFORCED;
	if (XFS_IS_PQUOTA_RUNNING(mp))
		state->s_state[PRJQUOTA].flags |= QCI_ACCT_ENABLED;
	if (XFS_IS_PQUOTA_ENFORCED(mp))
		state->s_state[PRJQUOTA].flags |= QCI_LIMITS_ENFORCED;

	xfs_qm_fill_state(&state->s_state[USRQUOTA], mp, q->qi_uquotaip,
			  mp->m_sb.sb_uquotino);
	xfs_qm_fill_state(&state->s_state[GRPQUOTA], mp, q->qi_gquotaip,
			  mp->m_sb.sb_gquotino);
	xfs_qm_fill_state(&state->s_state[PRJQUOTA], mp, q->qi_pquotaip,
			  mp->m_sb.sb_pquotino);
	return 0;
}