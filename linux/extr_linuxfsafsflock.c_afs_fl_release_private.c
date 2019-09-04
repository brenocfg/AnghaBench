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
struct file_lock {int /*<<< orphan*/  fl_file; } ;
struct afs_vnode {int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_state; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ,struct afs_vnode*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_dequeue_lock (struct afs_vnode*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_fl_release_private(struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(fl->fl_file));

	_enter("");

	spin_lock(&vnode->lock);
	afs_dequeue_lock(vnode, fl);
	_debug("state %u for %p", vnode->lock_state, vnode);
	spin_unlock(&vnode->lock);
}