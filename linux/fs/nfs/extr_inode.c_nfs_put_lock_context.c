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
struct nfs_open_context {int /*<<< orphan*/  dentry; } ;
struct nfs_lock_context {int /*<<< orphan*/  list; int /*<<< orphan*/  count; struct nfs_open_context* open_context; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfs_lock_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_nfs_open_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_put_lock_context(struct nfs_lock_context *l_ctx)
{
	struct nfs_open_context *ctx = l_ctx->open_context;
	struct inode *inode = d_inode(ctx->dentry);

	if (!refcount_dec_and_lock(&l_ctx->count, &inode->i_lock))
		return;
	list_del_rcu(&l_ctx->list);
	spin_unlock(&inode->i_lock);
	put_nfs_open_context(ctx);
	kfree_rcu(l_ctx, rcu_head);
}