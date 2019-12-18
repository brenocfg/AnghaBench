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
struct nfs_open_context {scalar_t__ error; int /*<<< orphan*/  dentry; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/  put_nfs_open_context_sync (struct nfs_open_context*) ; 

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
		put_nfs_open_context_sync(ctx);
	}
}