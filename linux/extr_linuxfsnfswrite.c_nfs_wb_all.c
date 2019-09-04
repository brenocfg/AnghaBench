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
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_SYNC ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int nfs_commit_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_sync_inode (struct inode*,int) ; 
 int /*<<< orphan*/  trace_nfs_writeback_inode_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_writeback_inode_exit (struct inode*,int) ; 

int nfs_wb_all(struct inode *inode)
{
	int ret;

	trace_nfs_writeback_inode_enter(inode);

	ret = filemap_write_and_wait(inode->i_mapping);
	if (ret)
		goto out;
	ret = nfs_commit_inode(inode, FLUSH_SYNC);
	if (ret < 0)
		goto out;
	pnfs_sync_inode(inode, true);
	ret = 0;

out:
	trace_nfs_writeback_inode_exit(inode, ret);
	return ret;
}