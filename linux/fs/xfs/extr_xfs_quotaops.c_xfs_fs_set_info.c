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
struct xfs_mount {int dummy; } ;
struct super_block {int dummy; } ;
struct qc_info {int i_fieldmask; int /*<<< orphan*/  i_rt_spc_warnlimit; int /*<<< orphan*/  i_spc_warnlimit; int /*<<< orphan*/  i_ino_warnlimit; int /*<<< orphan*/  i_rt_spc_timelimit; int /*<<< orphan*/  i_ino_timelimit; int /*<<< orphan*/  i_spc_timelimit; } ;
struct qc_dqblk {int d_fieldmask; int /*<<< orphan*/  d_rt_spc_warns; int /*<<< orphan*/  d_spc_warns; int /*<<< orphan*/  d_ino_warns; int /*<<< orphan*/  d_rt_spc_timer; int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_spc_timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int EROFS ; 
 int ESRCH ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (struct xfs_mount*) ; 
 struct xfs_mount* XFS_M (struct super_block*) ; 
 int XFS_QC_SETINFO_MASK ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int xfs_qm_scall_setqlim (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qc_dqblk*) ; 
 int /*<<< orphan*/  xfs_quota_type (int) ; 

__attribute__((used)) static int
xfs_fs_set_info(
	struct super_block	*sb,
	int			type,
	struct qc_info		*info)
{
	struct xfs_mount *mp = XFS_M(sb);
	struct qc_dqblk newlim;

	if (sb_rdonly(sb))
		return -EROFS;
	if (!XFS_IS_QUOTA_RUNNING(mp))
		return -ENOSYS;
	if (!XFS_IS_QUOTA_ON(mp))
		return -ESRCH;
	if (info->i_fieldmask & ~XFS_QC_SETINFO_MASK)
		return -EINVAL;
	if ((info->i_fieldmask & XFS_QC_SETINFO_MASK) == 0)
		return 0;

	newlim.d_fieldmask = info->i_fieldmask;
	newlim.d_spc_timer = info->i_spc_timelimit;
	newlim.d_ino_timer = info->i_ino_timelimit;
	newlim.d_rt_spc_timer = info->i_rt_spc_timelimit;
	newlim.d_ino_warns = info->i_ino_warnlimit;
	newlim.d_spc_warns = info->i_spc_warnlimit;
	newlim.d_rt_spc_warns = info->i_rt_spc_warnlimit;

	return xfs_qm_scall_setqlim(mp, 0, xfs_quota_type(type), &newlim);
}