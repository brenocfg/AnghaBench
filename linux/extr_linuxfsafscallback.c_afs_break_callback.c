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
struct afs_vnode {int /*<<< orphan*/  cb_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_locks; int /*<<< orphan*/  granted_locks; int /*<<< orphan*/  cb_break; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  AFS_VNODE_NEW_CONTENT ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_clear_permits (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_lock_may_be_available (struct afs_vnode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

void afs_break_callback(struct afs_vnode *vnode)
{
	_enter("");

	write_seqlock(&vnode->cb_lock);

	clear_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags);
	if (test_and_clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) {
		vnode->cb_break++;
		afs_clear_permits(vnode);

		spin_lock(&vnode->lock);

		_debug("break callback");

		if (list_empty(&vnode->granted_locks) &&
		    !list_empty(&vnode->pending_locks))
			afs_lock_may_be_available(vnode);
		spin_unlock(&vnode->lock);
	}

	write_sequnlock(&vnode->cb_lock);
}