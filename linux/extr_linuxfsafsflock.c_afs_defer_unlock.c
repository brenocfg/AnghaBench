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
struct afs_vnode {scalar_t__ lock_state; int /*<<< orphan*/  lock_work; } ;

/* Variables and functions */
 scalar_t__ AFS_VNODE_LOCK_EXTENDING ; 
 scalar_t__ AFS_VNODE_LOCK_GRANTED ; 
 scalar_t__ AFS_VNODE_LOCK_NEED_UNLOCK ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_lock_may_be_available (struct afs_vnode*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_defer_unlock(struct afs_vnode *vnode)
{
	_enter("");

	if (vnode->lock_state == AFS_VNODE_LOCK_GRANTED ||
	    vnode->lock_state == AFS_VNODE_LOCK_EXTENDING) {
		cancel_delayed_work(&vnode->lock_work);

		vnode->lock_state = AFS_VNODE_LOCK_NEED_UNLOCK;
		afs_lock_may_be_available(vnode);
	}
}