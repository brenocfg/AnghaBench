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
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ LLONG_MAX ; 
 struct inode* file_inode (struct file*) ; 
 int file_write_and_wait_range (struct file*,scalar_t__,scalar_t__) ; 
 int nfs_file_fsync_commit (struct file*,int) ; 
 int pnfs_sync_inode (struct inode*,int) ; 
 int /*<<< orphan*/  trace_nfs_fsync_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_fsync_exit (struct inode*,int) ; 

int
nfs_file_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	int ret;
	struct inode *inode = file_inode(file);

	trace_nfs_fsync_enter(inode);

	do {
		ret = file_write_and_wait_range(file, start, end);
		if (ret != 0)
			break;
		ret = nfs_file_fsync_commit(file, datasync);
		if (!ret)
			ret = pnfs_sync_inode(inode, !!datasync);
		/*
		 * If nfs_file_fsync_commit detected a server reboot, then
		 * resend all dirty pages that might have been covered by
		 * the NFS_CONTEXT_RESEND_WRITES flag
		 */
		start = 0;
		end = LLONG_MAX;
	} while (ret == -EAGAIN);

	trace_nfs_fsync_exit(inode, ret);
	return ret;
}