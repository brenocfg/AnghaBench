#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct nfs_open_context {int /*<<< orphan*/  mdsthreshold; int /*<<< orphan*/  ll_cred; TYPE_2__* dentry; int /*<<< orphan*/  cred; int /*<<< orphan*/  list; TYPE_1__ lock_context; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* close_context ) (struct nfs_open_context*,int) ;} ;
struct TYPE_6__ {struct super_block* d_sb; } ;

/* Variables and functions */
 TYPE_4__* NFS_PROTO (struct inode*) ; 
 struct inode* d_inode (TYPE_2__*) ; 
 int /*<<< orphan*/  dput (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfs_open_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs_open_context*,int) ; 

__attribute__((used)) static void __put_nfs_open_context(struct nfs_open_context *ctx, int is_sync)
{
	struct inode *inode = d_inode(ctx->dentry);
	struct super_block *sb = ctx->dentry->d_sb;

	if (!refcount_dec_and_test(&ctx->lock_context.count))
		return;
	if (!list_empty(&ctx->list)) {
		spin_lock(&inode->i_lock);
		list_del_rcu(&ctx->list);
		spin_unlock(&inode->i_lock);
	}
	if (inode != NULL)
		NFS_PROTO(inode)->close_context(ctx, is_sync);
	put_cred(ctx->cred);
	dput(ctx->dentry);
	nfs_sb_deactive(sb);
	put_rpccred(ctx->ll_cred);
	kfree(ctx->mdsthreshold);
	kfree_rcu(ctx, rcu_head);
}