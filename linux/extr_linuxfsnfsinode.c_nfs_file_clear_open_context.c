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
struct nfs_open_context {scalar_t__ error; int /*<<< orphan*/  list; int /*<<< orphan*/  dentry; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_mapping; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_files; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/  put_nfs_open_context_sync (struct nfs_open_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_file_clear_open_context(struct file *filp)
{
	struct nfs_open_context *ctx = nfs_file_open_context(filp);

	if (ctx) {
		struct inode *inode = d_inode(ctx->dentry);

		/*
		 * We fatal error on write before. Try to writeback
		 * every page again.
		 */
		if (ctx->error < 0)
			invalidate_inode_pages2(inode->i_mapping);
		filp->private_data = NULL;
		spin_lock(&inode->i_lock);
		list_move_tail(&ctx->list, &NFS_I(inode)->open_files);
		spin_unlock(&inode->i_lock);
		put_nfs_open_context_sync(ctx);
	}
}