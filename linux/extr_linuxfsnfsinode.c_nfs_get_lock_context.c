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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct nfs_open_context {TYPE_1__ lock_context; int /*<<< orphan*/  dentry; } ;
struct nfs_lock_context {struct nfs_open_context* open_context; int /*<<< orphan*/  list; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs_lock_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs_lock_context* __nfs_find_lock_context (struct nfs_open_context*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs_lock_context*) ; 
 struct nfs_lock_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_init_lock_context (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs_lock_context *nfs_get_lock_context(struct nfs_open_context *ctx)
{
	struct nfs_lock_context *res, *new = NULL;
	struct inode *inode = d_inode(ctx->dentry);

	spin_lock(&inode->i_lock);
	res = __nfs_find_lock_context(ctx);
	if (res == NULL) {
		spin_unlock(&inode->i_lock);
		new = kmalloc(sizeof(*new), GFP_KERNEL);
		if (new == NULL)
			return ERR_PTR(-ENOMEM);
		nfs_init_lock_context(new);
		spin_lock(&inode->i_lock);
		res = __nfs_find_lock_context(ctx);
		if (res == NULL) {
			list_add_tail(&new->list, &ctx->lock_context.list);
			new->open_context = ctx;
			res = new;
			new = NULL;
		}
	}
	spin_unlock(&inode->i_lock);
	kfree(new);
	return res;
}