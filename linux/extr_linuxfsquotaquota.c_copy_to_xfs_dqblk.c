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
struct qc_dqblk {int /*<<< orphan*/  d_rt_spc_warns; int /*<<< orphan*/  d_rt_spc_timer; int /*<<< orphan*/  d_rt_space; int /*<<< orphan*/  d_rt_spc_softlimit; int /*<<< orphan*/  d_rt_spc_hardlimit; int /*<<< orphan*/  d_spc_warns; int /*<<< orphan*/  d_ino_warns; int /*<<< orphan*/  d_spc_timer; int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_ino_count; int /*<<< orphan*/  d_space; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; int /*<<< orphan*/  d_spc_softlimit; int /*<<< orphan*/  d_spc_hardlimit; } ;
struct fs_disk_quota {int /*<<< orphan*/  d_rtbwarns; int /*<<< orphan*/  d_rtbtimer; void* d_rtbcount; void* d_rtb_softlimit; void* d_rtb_hardlimit; int /*<<< orphan*/  d_bwarns; int /*<<< orphan*/  d_iwarns; int /*<<< orphan*/  d_btimer; int /*<<< orphan*/  d_itimer; int /*<<< orphan*/  d_icount; void* d_bcount; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; void* d_blk_softlimit; void* d_blk_hardlimit; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_id; int /*<<< orphan*/  d_version; } ;
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FS_DQUOT_VERSION ; 
 int /*<<< orphan*/  FS_GROUP_QUOTA ; 
 int /*<<< orphan*/  FS_PROJ_QUOTA ; 
 int /*<<< orphan*/  FS_USER_QUOTA ; 
 int PRJQUOTA ; 
 int USRQUOTA ; 
 int /*<<< orphan*/  memset (struct fs_disk_quota*,int /*<<< orphan*/ ,int) ; 
 void* quota_btobb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_to_xfs_dqblk(struct fs_disk_quota *dst, struct qc_dqblk *src,
			      int type, qid_t id)
{
	memset(dst, 0, sizeof(*dst));
	dst->d_version = FS_DQUOT_VERSION;
	dst->d_id = id;
	if (type == USRQUOTA)
		dst->d_flags = FS_USER_QUOTA;
	else if (type == PRJQUOTA)
		dst->d_flags = FS_PROJ_QUOTA;
	else
		dst->d_flags = FS_GROUP_QUOTA;
	dst->d_blk_hardlimit = quota_btobb(src->d_spc_hardlimit);
	dst->d_blk_softlimit = quota_btobb(src->d_spc_softlimit);
	dst->d_ino_hardlimit = src->d_ino_hardlimit;
	dst->d_ino_softlimit = src->d_ino_softlimit;
	dst->d_bcount = quota_btobb(src->d_space);
	dst->d_icount = src->d_ino_count;
	dst->d_itimer = src->d_ino_timer;
	dst->d_btimer = src->d_spc_timer;
	dst->d_iwarns = src->d_ino_warns;
	dst->d_bwarns = src->d_spc_warns;
	dst->d_rtb_hardlimit = quota_btobb(src->d_rt_spc_hardlimit);
	dst->d_rtb_softlimit = quota_btobb(src->d_rt_spc_softlimit);
	dst->d_rtbcount = quota_btobb(src->d_rt_space);
	dst->d_rtbtimer = src->d_rt_spc_timer;
	dst->d_rtbwarns = src->d_rt_spc_warns;
}