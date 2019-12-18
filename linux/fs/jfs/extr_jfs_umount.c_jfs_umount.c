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
struct jfs_sb_info {TYPE_1__* direct_inode; struct inode* ipimap; struct inode* ipaimap; struct inode* ipaimap2; struct jfs_log* log; struct inode* ipbmap; } ;
struct jfs_log {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLEAN ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  dbUnmount (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diFreeSpecial (struct inode*) ; 
 int /*<<< orphan*/  diUnmount (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_flush_journal (struct jfs_log*,int) ; 
 int /*<<< orphan*/  jfs_info (char*,int) ; 
 int lmLogClose (struct super_block*) ; 
 int /*<<< orphan*/  updateSuper (struct super_block*,int /*<<< orphan*/ ) ; 

int jfs_umount(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	struct inode *ipbmap = sbi->ipbmap;
	struct inode *ipimap = sbi->ipimap;
	struct inode *ipaimap = sbi->ipaimap;
	struct inode *ipaimap2 = sbi->ipaimap2;
	struct jfs_log *log;
	int rc = 0;

	jfs_info("UnMount JFS: sb:0x%p", sb);

	/*
	 *	update superblock and close log
	 *
	 * if mounted read-write and log based recovery was enabled
	 */
	if ((log = sbi->log))
		/*
		 * Wait for outstanding transactions to be written to log:
		 */
		jfs_flush_journal(log, 2);

	/*
	 * close fileset inode allocation map (aka fileset inode)
	 */
	diUnmount(ipimap, 0);

	diFreeSpecial(ipimap);
	sbi->ipimap = NULL;

	/*
	 * close secondary aggregate inode allocation map
	 */
	ipaimap2 = sbi->ipaimap2;
	if (ipaimap2) {
		diUnmount(ipaimap2, 0);
		diFreeSpecial(ipaimap2);
		sbi->ipaimap2 = NULL;
	}

	/*
	 * close aggregate inode allocation map
	 */
	ipaimap = sbi->ipaimap;
	diUnmount(ipaimap, 0);
	diFreeSpecial(ipaimap);
	sbi->ipaimap = NULL;

	/*
	 * close aggregate block allocation map
	 */
	dbUnmount(ipbmap, 0);

	diFreeSpecial(ipbmap);
	sbi->ipimap = NULL;

	/*
	 * Make sure all metadata makes it to disk before we mark
	 * the superblock as clean
	 */
	filemap_write_and_wait(sbi->direct_inode->i_mapping);

	/*
	 * ensure all file system file pages are propagated to their
	 * home blocks on disk (and their in-memory buffer pages are
	 * invalidated) BEFORE updating file system superblock state
	 * (to signify file system is unmounted cleanly, and thus in
	 * consistent state) and log superblock active file system
	 * list (to signify skip logredo()).
	 */
	if (log) {		/* log = NULL if read-only mount */
		updateSuper(sb, FM_CLEAN);

		/*
		 * close log:
		 *
		 * remove file system from log active file system list.
		 */
		rc = lmLogClose(sb);
	}
	jfs_info("UnMount JFS Complete: rc = %d", rc);
	return rc;
}