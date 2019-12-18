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
struct nfs_open_dir_context {int /*<<< orphan*/  list; int /*<<< orphan*/  cred; scalar_t__ dup_cookie; scalar_t__ dir_cookie; int /*<<< orphan*/  attr_gencount; scalar_t__ duped; } ;
struct nfs_inode {int cache_validity; int /*<<< orphan*/  open_files; int /*<<< orphan*/  attr_gencount; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs_open_dir_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_DATA_INVAL_DEFER ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_REVAL_FORCED ; 
 int /*<<< orphan*/  get_cred (struct cred const*) ; 
 struct nfs_open_dir_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_open_dir_context *alloc_nfs_open_dir_context(struct inode *dir, const struct cred *cred)
{
	struct nfs_inode *nfsi = NFS_I(dir);
	struct nfs_open_dir_context *ctx;
	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (ctx != NULL) {
		ctx->duped = 0;
		ctx->attr_gencount = nfsi->attr_gencount;
		ctx->dir_cookie = 0;
		ctx->dup_cookie = 0;
		ctx->cred = get_cred(cred);
		spin_lock(&dir->i_lock);
		if (list_empty(&nfsi->open_files) &&
		    (nfsi->cache_validity & NFS_INO_DATA_INVAL_DEFER))
			nfsi->cache_validity |= NFS_INO_INVALID_DATA |
				NFS_INO_REVAL_FORCED;
		list_add(&ctx->list, &nfsi->open_files);
		spin_unlock(&dir->i_lock);
		return ctx;
	}
	return  ERR_PTR(-ENOMEM);
}