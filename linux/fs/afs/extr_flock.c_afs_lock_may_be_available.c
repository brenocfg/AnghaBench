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
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {scalar_t__ lock_state; int /*<<< orphan*/  lock; TYPE_1__ fid; } ;

/* Variables and functions */
 scalar_t__ AFS_VNODE_LOCK_WAITING_FOR_CB ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_flock_callback_break ; 
 int /*<<< orphan*/  afs_next_locker (struct afs_vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_flock_ev (struct afs_vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void afs_lock_may_be_available(struct afs_vnode *vnode)
{
	_enter("{%llx:%llu}", vnode->fid.vid, vnode->fid.vnode);

	spin_lock(&vnode->lock);
	if (vnode->lock_state == AFS_VNODE_LOCK_WAITING_FOR_CB)
		afs_next_locker(vnode, 0);
	trace_afs_flock_ev(vnode, NULL, afs_flock_callback_break, 0);
	spin_unlock(&vnode->lock);
}