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
struct afs_vnode {int flags; struct inode vfs_inode; int /*<<< orphan*/  rmdir_lock; int /*<<< orphan*/  lock_state; int /*<<< orphan*/ * cache; int /*<<< orphan*/  cb_interest; int /*<<< orphan*/ * permit_cache; int /*<<< orphan*/ * lock_key; int /*<<< orphan*/ * volume; int /*<<< orphan*/  status; int /*<<< orphan*/  fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_LOCK_NONE ; 
 int AFS_VNODE_UNSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _leave (char*,struct inode*) ; 
 int /*<<< orphan*/  afs_count_active_inodes ; 
 int /*<<< orphan*/  afs_inode_cachep ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct afs_vnode* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct inode *afs_alloc_inode(struct super_block *sb)
{
	struct afs_vnode *vnode;

	vnode = kmem_cache_alloc(afs_inode_cachep, GFP_KERNEL);
	if (!vnode)
		return NULL;

	atomic_inc(&afs_count_active_inodes);

	/* Reset anything that shouldn't leak from one inode to the next. */
	memset(&vnode->fid, 0, sizeof(vnode->fid));
	memset(&vnode->status, 0, sizeof(vnode->status));

	vnode->volume		= NULL;
	vnode->lock_key		= NULL;
	vnode->permit_cache	= NULL;
	RCU_INIT_POINTER(vnode->cb_interest, NULL);
#ifdef CONFIG_AFS_FSCACHE
	vnode->cache		= NULL;
#endif

	vnode->flags		= 1 << AFS_VNODE_UNSET;
	vnode->lock_state	= AFS_VNODE_LOCK_NONE;

	init_rwsem(&vnode->rmdir_lock);

	_leave(" = %p", &vnode->vfs_inode);
	return &vnode->vfs_inode;
}