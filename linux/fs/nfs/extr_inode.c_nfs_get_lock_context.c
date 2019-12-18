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
struct nfs_lock_context {int /*<<< orphan*/  list; scalar_t__ open_context; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs_lock_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs_lock_context* __nfs_find_lock_context (struct nfs_open_context*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ get_nfs_open_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  kfree (struct nfs_lock_context*) ; 
 struct nfs_lock_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_init_lock_context (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs_lock_context *nfs_get_lock_context(struct nfs_open_context *ctx)
{
	struct nfs_lock_context *res, *new = NULL;
	struct inode *inode = d_inode(ctx->dentry);

	rcu_read_lock();
	res = __nfs_find_lock_context(ctx);
	rcu_read_unlock();
	if (res == NULL) {
		new = kmalloc(sizeof(*new), GFP_KERNEL);
		if (new == NULL)
			return ERR_PTR(-ENOMEM);
		nfs_init_lock_context(new);
		spin_lock(&inode->i_lock);
		res = __nfs_find_lock_context(ctx);
		if (res == NULL) {
			new->open_context = get_nfs_open_context(ctx);
			if (new->open_context) {
				list_add_tail_rcu(&new->list,
						&ctx->lock_context.list);
				res = new;
				new = NULL;
			} else
				res = ERR_PTR(-EBADF);
		}
		spin_unlock(&inode->i_lock);
		kfree(new);
	}
	return res;
}