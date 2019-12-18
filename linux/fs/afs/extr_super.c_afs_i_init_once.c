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
struct afs_vnode {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  lock_work; int /*<<< orphan*/  granted_locks; int /*<<< orphan*/  pending_locks; int /*<<< orphan*/  wb_keys; int /*<<< orphan*/  lock; int /*<<< orphan*/  wb_lock; int /*<<< orphan*/  validate_lock; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_lock_work ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct afs_vnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_i_init_once(void *_vnode)
{
	struct afs_vnode *vnode = _vnode;

	memset(vnode, 0, sizeof(*vnode));
	inode_init_once(&vnode->vfs_inode);
	mutex_init(&vnode->io_lock);
	init_rwsem(&vnode->validate_lock);
	spin_lock_init(&vnode->wb_lock);
	spin_lock_init(&vnode->lock);
	INIT_LIST_HEAD(&vnode->wb_keys);
	INIT_LIST_HEAD(&vnode->pending_locks);
	INIT_LIST_HEAD(&vnode->granted_locks);
	INIT_DELAYED_WORK(&vnode->lock_work, afs_lock_work);
	seqlock_init(&vnode->cb_lock);
}