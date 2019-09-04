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
struct qc_info {int /*<<< orphan*/  i_fieldmask; int /*<<< orphan*/  i_rt_spc_warnlimit; int /*<<< orphan*/  i_spc_warnlimit; int /*<<< orphan*/  i_ino_warnlimit; int /*<<< orphan*/  i_rt_spc_timelimit; int /*<<< orphan*/  i_ino_timelimit; int /*<<< orphan*/  i_spc_timelimit; } ;
struct fs_disk_quota {int d_fieldmask; int /*<<< orphan*/  d_rtbwarns; int /*<<< orphan*/  d_bwarns; int /*<<< orphan*/  d_iwarns; int /*<<< orphan*/  d_rtbtimer; int /*<<< orphan*/  d_itimer; int /*<<< orphan*/  d_btimer; } ;

/* Variables and functions */
 int FS_DQ_BTIMER ; 
 int FS_DQ_BWARNS ; 
 int FS_DQ_ITIMER ; 
 int FS_DQ_IWARNS ; 
 int FS_DQ_RTBTIMER ; 
 int FS_DQ_RTBWARNS ; 
 int /*<<< orphan*/  QC_INO_TIMER ; 
 int /*<<< orphan*/  QC_INO_WARNS ; 
 int /*<<< orphan*/  QC_RT_SPC_TIMER ; 
 int /*<<< orphan*/  QC_RT_SPC_WARNS ; 
 int /*<<< orphan*/  QC_SPC_TIMER ; 
 int /*<<< orphan*/  QC_SPC_WARNS ; 
 int /*<<< orphan*/  memset (struct qc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copy_qcinfo_from_xfs_dqblk(struct qc_info *dst,
				       struct fs_disk_quota *src)
{
	memset(dst, 0, sizeof(*dst));
	dst->i_spc_timelimit = src->d_btimer;
	dst->i_ino_timelimit = src->d_itimer;
	dst->i_rt_spc_timelimit = src->d_rtbtimer;
	dst->i_ino_warnlimit = src->d_iwarns;
	dst->i_spc_warnlimit = src->d_bwarns;
	dst->i_rt_spc_warnlimit = src->d_rtbwarns;
	if (src->d_fieldmask & FS_DQ_BWARNS)
		dst->i_fieldmask |= QC_SPC_WARNS;
	if (src->d_fieldmask & FS_DQ_IWARNS)
		dst->i_fieldmask |= QC_INO_WARNS;
	if (src->d_fieldmask & FS_DQ_RTBWARNS)
		dst->i_fieldmask |= QC_RT_SPC_WARNS;
	if (src->d_fieldmask & FS_DQ_BTIMER)
		dst->i_fieldmask |= QC_SPC_TIMER;
	if (src->d_fieldmask & FS_DQ_ITIMER)
		dst->i_fieldmask |= QC_INO_TIMER;
	if (src->d_fieldmask & FS_DQ_RTBTIMER)
		dst->i_fieldmask |= QC_RT_SPC_TIMER;
}