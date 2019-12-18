#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct TYPE_4__ {TYPE_1__ afs; } ;
struct file_lock {TYPE_2__ fl_u; int /*<<< orphan*/  fl_file; } ;
struct afs_vnode {int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_state; int /*<<< orphan*/  granted_locks; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ,struct afs_vnode*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_defer_unlock (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_flock_op_release_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_flock_op (struct afs_vnode*,struct file_lock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afs_fl_release_private(struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(fl->fl_file));

	_enter("");

	spin_lock(&vnode->lock);

	trace_afs_flock_op(vnode, fl, afs_flock_op_release_lock);
	list_del_init(&fl->fl_u.afs.link);
	if (list_empty(&vnode->granted_locks))
		afs_defer_unlock(vnode);

	_debug("state %u for %p", vnode->lock_state, vnode);
	spin_unlock(&vnode->lock);
}