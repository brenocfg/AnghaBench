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
struct nfs_open_context {int /*<<< orphan*/  error; int /*<<< orphan*/  flags; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  NFS_CONTEXT_ERROR_WRITE ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_file_fsync_commit (struct file*,int) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int pnfs_sync_inode (struct inode*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs_fsync_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_fsync_exit (struct inode*,int) ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nfs_file_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	int ret;
	struct inode *inode = file_inode(file);

	trace_nfs_fsync_enter(inode);

	do {
		struct nfs_open_context *ctx = nfs_file_open_context(file);
		ret = filemap_write_and_wait_range(inode->i_mapping, start, end);
		if (test_and_clear_bit(NFS_CONTEXT_ERROR_WRITE, &ctx->flags)) {
			int ret2 = xchg(&ctx->error, 0);
			if (ret2)
				ret = ret2;
		}
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