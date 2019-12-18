#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_bdev; TYPE_1__* s_op; } ;
struct quota_info {int flags; TYPE_2__** files; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sync_fs ) (struct super_block*,int) ;} ;

/* Variables and functions */
 int DQUOT_QUOTA_SYS_FILE ; 
 int MAXQUOTAS ; 
 int dquot_writeback_dquots (struct super_block*,int) ; 
 int /*<<< orphan*/  inode_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 
 int /*<<< orphan*/  sync_blockdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dquot_quota_sync(struct super_block *sb, int type)
{
	struct quota_info *dqopt = sb_dqopt(sb);
	int cnt;
	int ret;

	ret = dquot_writeback_dquots(sb, type);
	if (ret)
		return ret;
	if (dqopt->flags & DQUOT_QUOTA_SYS_FILE)
		return 0;

	/* This is not very clever (and fast) but currently I don't know about
	 * any other simple way of getting quota data to disk and we must get
	 * them there for userspace to be visible... */
	if (sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, 1);
	sync_blockdev(sb->s_bdev);

	/*
	 * Now when everything is written we can discard the pagecache so
	 * that userspace sees the changes.
	 */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (type != -1 && cnt != type)
			continue;
		if (!sb_has_quota_active(sb, cnt))
			continue;
		inode_lock(dqopt->files[cnt]);
		truncate_inode_pages(&dqopt->files[cnt]->i_data, 0);
		inode_unlock(dqopt->files[cnt]);
	}

	return 0;
}