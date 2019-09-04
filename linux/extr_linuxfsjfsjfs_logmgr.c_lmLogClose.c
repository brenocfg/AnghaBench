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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct jfs_sb_info {struct jfs_log* log; int /*<<< orphan*/  log_list; } ;
struct jfs_log {struct block_device* bdev; int /*<<< orphan*/  journal_list; scalar_t__ no_integrity; int /*<<< orphan*/  sb_list; int /*<<< orphan*/  flag; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  LOG_LOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  LOG_UNLOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int) ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int /*<<< orphan*/  jfs_log_mutex ; 
 int /*<<< orphan*/  kfree (struct jfs_log*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmLogFileSystem (struct jfs_log*,struct jfs_sb_info*,int /*<<< orphan*/ ) ; 
 int lmLogShutdown (struct jfs_log*) ; 
 int /*<<< orphan*/  log_INLINELOG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_blockdev (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int lmLogClose(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	struct jfs_log *log = sbi->log;
	struct block_device *bdev;
	int rc = 0;

	jfs_info("lmLogClose: log:0x%p", log);

	mutex_lock(&jfs_log_mutex);
	LOG_LOCK(log);
	list_del(&sbi->log_list);
	LOG_UNLOCK(log);
	sbi->log = NULL;

	/*
	 * We need to make sure all of the "written" metapages
	 * actually make it to disk
	 */
	sync_blockdev(sb->s_bdev);

	if (test_bit(log_INLINELOG, &log->flag)) {
		/*
		 *	in-line log in host file system
		 */
		rc = lmLogShutdown(log);
		kfree(log);
		goto out;
	}

	if (!log->no_integrity)
		lmLogFileSystem(log, sbi, 0);

	if (!list_empty(&log->sb_list))
		goto out;

	/*
	 * TODO: ensure that the dummy_log is in a state to allow
	 * lbmLogShutdown to deallocate all the buffers and call
	 * kfree against dummy_log.  For now, leave dummy_log & its
	 * buffers in memory, and resuse if another no-integrity mount
	 * is requested.
	 */
	if (log->no_integrity)
		goto out;

	/*
	 *	external log as separate logical volume
	 */
	list_del(&log->journal_list);
	bdev = log->bdev;
	rc = lmLogShutdown(log);

	blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);

	kfree(log);

      out:
	mutex_unlock(&jfs_log_mutex);
	jfs_info("lmLogClose: exit(%d)", rc);
	return rc;
}