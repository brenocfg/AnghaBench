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
struct afs_vnode {scalar_t__ lock_state; int /*<<< orphan*/  lock_work; int /*<<< orphan*/  granted_locks; } ;

/* Variables and functions */
 scalar_t__ AFS_VNODE_LOCK_EXTENDING ; 
 scalar_t__ AFS_VNODE_LOCK_GRANTED ; 
 int /*<<< orphan*/  AFS_VNODE_LOCK_NEED_UNLOCK ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__) ; 
 int /*<<< orphan*/  afs_flock_defer_unlock ; 
 int /*<<< orphan*/  afs_lock_manager ; 
 int /*<<< orphan*/  afs_set_lock_state (struct afs_vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_flock_ev (struct afs_vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afs_defer_unlock(struct afs_vnode *vnode)
{
	_enter("%u", vnode->lock_state);

	if (list_empty(&vnode->granted_locks) &&
	    (vnode->lock_state == AFS_VNODE_LOCK_GRANTED ||
	     vnode->lock_state == AFS_VNODE_LOCK_EXTENDING)) {
		cancel_delayed_work(&vnode->lock_work);

		afs_set_lock_state(vnode, AFS_VNODE_LOCK_NEED_UNLOCK);
		trace_afs_flock_ev(vnode, NULL, afs_flock_defer_unlock, 0);
		queue_delayed_work(afs_lock_manager, &vnode->lock_work, 0);
	}
}