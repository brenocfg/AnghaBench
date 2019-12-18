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
struct writeback_control {scalar_t__ sync_mode; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Dirty ; 
 int EIO ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ jfs_commit_inode (struct inode*,int) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  jfs_flush_journal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct inode*) ; 

int jfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int wait = wbc->sync_mode == WB_SYNC_ALL;

	if (inode->i_nlink == 0)
		return 0;
	/*
	 * If COMMIT_DIRTY is not set, the inode isn't really dirty.
	 * It has been committed since the last change, but was still
	 * on the dirty inode list.
	 */
	if (!test_cflag(COMMIT_Dirty, inode)) {
		/* Make sure committed changes hit the disk */
		jfs_flush_journal(JFS_SBI(inode->i_sb)->log, wait);
		return 0;
	}

	if (jfs_commit_inode(inode, wait)) {
		jfs_err("jfs_write_inode: jfs_commit_inode failed!");
		return -EIO;
	} else
		return 0;
}