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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_inode {struct inode inode; int /*<<< orphan*/  forget; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; scalar_t__ state; scalar_t__ orig_ino; scalar_t__ attr_version; scalar_t__ nlookup; scalar_t__ nodeid; scalar_t__ inval_mask; scalar_t__ i_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fuse_alloc_forget () ; 
 int /*<<< orphan*/  fuse_inode_cachep ; 
 struct fuse_inode* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fuse_inode*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *fuse_alloc_inode(struct super_block *sb)
{
	struct fuse_inode *fi;

	fi = kmem_cache_alloc(fuse_inode_cachep, GFP_KERNEL);
	if (!fi)
		return NULL;

	fi->i_time = 0;
	fi->inval_mask = 0;
	fi->nodeid = 0;
	fi->nlookup = 0;
	fi->attr_version = 0;
	fi->orig_ino = 0;
	fi->state = 0;
	mutex_init(&fi->mutex);
	spin_lock_init(&fi->lock);
	fi->forget = fuse_alloc_forget();
	if (!fi->forget) {
		kmem_cache_free(fuse_inode_cachep, fi);
		return NULL;
	}

	return &fi->inode;
}