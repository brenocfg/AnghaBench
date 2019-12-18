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
struct nfs_open_context {int /*<<< orphan*/  list; int /*<<< orphan*/  dentry; } ;
struct nfs_inode {int cache_validity; int /*<<< orphan*/  open_files; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_DATA_INVAL_DEFER ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_REVAL_FORCED ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_inode_attach_open_context(struct nfs_open_context *ctx)
{
	struct inode *inode = d_inode(ctx->dentry);
	struct nfs_inode *nfsi = NFS_I(inode);

	spin_lock(&inode->i_lock);
	if (list_empty(&nfsi->open_files) &&
	    (nfsi->cache_validity & NFS_INO_DATA_INVAL_DEFER))
		nfsi->cache_validity |= NFS_INO_INVALID_DATA |
			NFS_INO_REVAL_FORCED;
	list_add_tail_rcu(&ctx->list, &nfsi->open_files);
	spin_unlock(&inode->i_lock);
}