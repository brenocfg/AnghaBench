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
struct super_block {int dummy; } ;
struct jfs_sb_info {TYPE_1__* direct_inode; int /*<<< orphan*/  ipimap; int /*<<< orphan*/  ipbmap; struct jfs_log* log; } ;
struct jfs_log {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLEAN ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  dbSync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diSync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_flush_journal (struct jfs_log*,int) ; 
 int lmLogClose (struct super_block*) ; 
 int /*<<< orphan*/  updateSuper (struct super_block*,int /*<<< orphan*/ ) ; 

int jfs_umount_rw(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	struct jfs_log *log = sbi->log;

	if (!log)
		return 0;

	/*
	 * close log:
	 *
	 * remove file system from log active file system list.
	 */
	jfs_flush_journal(log, 2);

	/*
	 * Make sure all metadata makes it to disk
	 */
	dbSync(sbi->ipbmap);
	diSync(sbi->ipimap);

	/*
	 * Note that we have to do this even if sync_blockdev() will
	 * do exactly the same a few instructions later:  We can't
	 * mark the superblock clean before everything is flushed to
	 * disk.
	 */
	filemap_write_and_wait(sbi->direct_inode->i_mapping);

	updateSuper(sb, FM_CLEAN);

	return lmLogClose(sb);
}