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
struct qc_dqblk {int /*<<< orphan*/  d_fieldmask; int /*<<< orphan*/  d_rt_spc_warns; int /*<<< orphan*/  d_rt_spc_timer; void* d_rt_space; void* d_rt_spc_softlimit; void* d_rt_spc_hardlimit; int /*<<< orphan*/  d_spc_warns; int /*<<< orphan*/  d_ino_warns; int /*<<< orphan*/  d_spc_timer; int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_ino_count; void* d_space; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; void* d_spc_softlimit; void* d_spc_hardlimit; } ;
struct fs_disk_quota {int d_fieldmask; int /*<<< orphan*/  d_rtbwarns; int /*<<< orphan*/  d_rtbtimer; int /*<<< orphan*/  d_rtbcount; int /*<<< orphan*/  d_rtb_softlimit; int /*<<< orphan*/  d_rtb_hardlimit; int /*<<< orphan*/  d_bwarns; int /*<<< orphan*/  d_iwarns; int /*<<< orphan*/  d_btimer; int /*<<< orphan*/  d_itimer; int /*<<< orphan*/  d_icount; int /*<<< orphan*/  d_bcount; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; int /*<<< orphan*/  d_blk_softlimit; int /*<<< orphan*/  d_blk_hardlimit; } ;

/* Variables and functions */
 int FS_DQ_BCOUNT ; 
 int FS_DQ_BHARD ; 
 int FS_DQ_BSOFT ; 
 int FS_DQ_BTIMER ; 
 int FS_DQ_BWARNS ; 
 int FS_DQ_ICOUNT ; 
 int FS_DQ_IHARD ; 
 int FS_DQ_ISOFT ; 
 int FS_DQ_ITIMER ; 
 int FS_DQ_IWARNS ; 
 int FS_DQ_RTBCOUNT ; 
 int FS_DQ_RTBHARD ; 
 int FS_DQ_RTBSOFT ; 
 int FS_DQ_RTBTIMER ; 
 int FS_DQ_RTBWARNS ; 
 int /*<<< orphan*/  QC_INO_COUNT ; 
 int /*<<< orphan*/  QC_INO_HARD ; 
 int /*<<< orphan*/  QC_INO_SOFT ; 
 int /*<<< orphan*/  QC_INO_TIMER ; 
 int /*<<< orphan*/  QC_INO_WARNS ; 
 int /*<<< orphan*/  QC_RT_SPACE ; 
 int /*<<< orphan*/  QC_RT_SPC_HARD ; 
 int /*<<< orphan*/  QC_RT_SPC_SOFT ; 
 int /*<<< orphan*/  QC_RT_SPC_TIMER ; 
 int /*<<< orphan*/  QC_RT_SPC_WARNS ; 
 int /*<<< orphan*/  QC_SPACE ; 
 int /*<<< orphan*/  QC_SPC_HARD ; 
 int /*<<< orphan*/  QC_SPC_SOFT ; 
 int /*<<< orphan*/  QC_SPC_TIMER ; 
 int /*<<< orphan*/  QC_SPC_WARNS ; 
 void* quota_bbtob (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_from_xfs_dqblk(struct qc_dqblk *dst, struct fs_disk_quota *src)
{
	dst->d_spc_hardlimit = quota_bbtob(src->d_blk_hardlimit);
	dst->d_spc_softlimit = quota_bbtob(src->d_blk_softlimit);
	dst->d_ino_hardlimit = src->d_ino_hardlimit;
	dst->d_ino_softlimit = src->d_ino_softlimit;
	dst->d_space = quota_bbtob(src->d_bcount);
	dst->d_ino_count = src->d_icount;
	dst->d_ino_timer = src->d_itimer;
	dst->d_spc_timer = src->d_btimer;
	dst->d_ino_warns = src->d_iwarns;
	dst->d_spc_warns = src->d_bwarns;
	dst->d_rt_spc_hardlimit = quota_bbtob(src->d_rtb_hardlimit);
	dst->d_rt_spc_softlimit = quota_bbtob(src->d_rtb_softlimit);
	dst->d_rt_space = quota_bbtob(src->d_rtbcount);
	dst->d_rt_spc_timer = src->d_rtbtimer;
	dst->d_rt_spc_warns = src->d_rtbwarns;
	dst->d_fieldmask = 0;
	if (src->d_fieldmask & FS_DQ_ISOFT)
		dst->d_fieldmask |= QC_INO_SOFT;
	if (src->d_fieldmask & FS_DQ_IHARD)
		dst->d_fieldmask |= QC_INO_HARD;
	if (src->d_fieldmask & FS_DQ_BSOFT)
		dst->d_fieldmask |= QC_SPC_SOFT;
	if (src->d_fieldmask & FS_DQ_BHARD)
		dst->d_fieldmask |= QC_SPC_HARD;
	if (src->d_fieldmask & FS_DQ_RTBSOFT)
		dst->d_fieldmask |= QC_RT_SPC_SOFT;
	if (src->d_fieldmask & FS_DQ_RTBHARD)
		dst->d_fieldmask |= QC_RT_SPC_HARD;
	if (src->d_fieldmask & FS_DQ_BTIMER)
		dst->d_fieldmask |= QC_SPC_TIMER;
	if (src->d_fieldmask & FS_DQ_ITIMER)
		dst->d_fieldmask |= QC_INO_TIMER;
	if (src->d_fieldmask & FS_DQ_RTBTIMER)
		dst->d_fieldmask |= QC_RT_SPC_TIMER;
	if (src->d_fieldmask & FS_DQ_BWARNS)
		dst->d_fieldmask |= QC_SPC_WARNS;
	if (src->d_fieldmask & FS_DQ_IWARNS)
		dst->d_fieldmask |= QC_INO_WARNS;
	if (src->d_fieldmask & FS_DQ_RTBWARNS)
		dst->d_fieldmask |= QC_RT_SPC_WARNS;
	if (src->d_fieldmask & FS_DQ_BCOUNT)
		dst->d_fieldmask |= QC_SPACE;
	if (src->d_fieldmask & FS_DQ_ICOUNT)
		dst->d_fieldmask |= QC_INO_COUNT;
	if (src->d_fieldmask & FS_DQ_RTBCOUNT)
		dst->d_fieldmask |= QC_RT_SPACE;
}