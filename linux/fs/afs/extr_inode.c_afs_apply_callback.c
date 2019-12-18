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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct afs_vnode {int /*<<< orphan*/  flags; int /*<<< orphan*/  cb_interest; TYPE_1__ cb_lock; int /*<<< orphan*/  cb_expires_at; } ;
struct afs_callback {int /*<<< orphan*/  expires_at; } ;
struct afs_status_cb {struct afs_callback callback; } ;
struct afs_fs_cursor {struct afs_cb_interest* cbi; } ;
struct afs_cb_interest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_CB_PROMISED ; 
 int /*<<< orphan*/  afs_cb_is_broken (unsigned int,struct afs_vnode*,struct afs_cb_interest*) ; 
 int /*<<< orphan*/  afs_get_cb_interest (struct afs_cb_interest*) ; 
 int /*<<< orphan*/  afs_put_cb_interest (int /*<<< orphan*/ ,struct afs_cb_interest*) ; 
 int /*<<< orphan*/  afs_v2net (struct afs_vnode*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct afs_cb_interest* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_apply_callback(struct afs_fs_cursor *fc,
			       struct afs_vnode *vnode,
			       struct afs_status_cb *scb,
			       unsigned int cb_break)
{
	struct afs_cb_interest *old;
	struct afs_callback *cb = &scb->callback;

	if (!afs_cb_is_broken(cb_break, vnode, fc->cbi)) {
		vnode->cb_expires_at	= cb->expires_at;
		old = rcu_dereference_protected(vnode->cb_interest,
						lockdep_is_held(&vnode->cb_lock.lock));
		if (old != fc->cbi) {
			rcu_assign_pointer(vnode->cb_interest, afs_get_cb_interest(fc->cbi));
			afs_put_cb_interest(afs_v2net(vnode), old);
		}
		set_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
	}
}