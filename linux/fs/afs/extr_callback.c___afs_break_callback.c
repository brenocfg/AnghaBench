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
struct afs_vnode {scalar_t__ lock_state; int /*<<< orphan*/  cb_break; int /*<<< orphan*/  fid; int /*<<< orphan*/  flags; } ;
typedef  enum afs_cb_break_reason { ____Placeholder_afs_cb_break_reason } afs_cb_break_reason ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 scalar_t__ AFS_VNODE_LOCK_WAITING_FOR_CB ; 
 int /*<<< orphan*/  AFS_VNODE_NEW_CONTENT ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_clear_permits (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_lock_may_be_available (struct afs_vnode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_cb_break (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void __afs_break_callback(struct afs_vnode *vnode, enum afs_cb_break_reason reason)
{
	_enter("");

	clear_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags);
	if (test_and_clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) {
		vnode->cb_break++;
		afs_clear_permits(vnode);

		if (vnode->lock_state == AFS_VNODE_LOCK_WAITING_FOR_CB)
			afs_lock_may_be_available(vnode);

		trace_afs_cb_break(&vnode->fid, vnode->cb_break, reason, true);
	} else {
		trace_afs_cb_break(&vnode->fid, vnode->cb_break, reason, false);
	}
}