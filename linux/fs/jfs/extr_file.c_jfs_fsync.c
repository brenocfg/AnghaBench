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
struct inode {int i_state; int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int I_DIRTY_ALL ; 
 int I_DIRTY_DATASYNC ; 
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int jfs_commit_inode (struct inode*,int) ; 
 int /*<<< orphan*/  jfs_flush_journal (int /*<<< orphan*/ ,int) ; 

int jfs_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = file->f_mapping->host;
	int rc = 0;

	rc = file_write_and_wait_range(file, start, end);
	if (rc)
		return rc;

	inode_lock(inode);
	if (!(inode->i_state & I_DIRTY_ALL) ||
	    (datasync && !(inode->i_state & I_DIRTY_DATASYNC))) {
		/* Make sure committed changes hit the disk */
		jfs_flush_journal(JFS_SBI(inode->i_sb)->log, 1);
		inode_unlock(inode);
		return rc;
	}

	rc |= jfs_commit_inode(inode, 1);
	inode_unlock(inode);

	return rc ? -EIO : 0;
}