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
struct ceph_mds_session {scalar_t__ s_cap_gen; int /*<<< orphan*/  s_cap_lock; int /*<<< orphan*/  s_cap_reconnect; int /*<<< orphan*/  s_nr_caps; struct ceph_cap* s_cap_iterator; int /*<<< orphan*/  i_sb; } ;
struct ceph_mds_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ino; } ;
struct ceph_inode_info {scalar_t__ i_wr_ref; scalar_t__ i_snap_realm; TYPE_1__ i_vino; struct ceph_cap* i_auth_cap; int /*<<< orphan*/  i_caps; struct ceph_mds_session vfs_inode; } ;
struct ceph_cap {scalar_t__ cap_gen; int queue_release; int /*<<< orphan*/  cap_ino; struct ceph_inode_info* ci; struct ceph_mds_session* session; int /*<<< orphan*/  session_caps; int /*<<< orphan*/  ci_node; } ;
struct TYPE_4__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cap_delay_cancel (struct ceph_mds_client*,struct ceph_inode_info*) ; 
 int /*<<< orphan*/  __ceph_is_any_caps (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  __ceph_is_any_real_caps (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  __ceph_queue_cap_release (struct ceph_mds_session*,struct ceph_cap*) ; 
 int /*<<< orphan*/  ceph_put_cap (struct ceph_mds_client*,struct ceph_cap*) ; 
 TYPE_2__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_cap*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  drop_inode_snap_realm (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __ceph_remove_cap(struct ceph_cap *cap, bool queue_release)
{
	struct ceph_mds_session *session = cap->session;
	struct ceph_inode_info *ci = cap->ci;
	struct ceph_mds_client *mdsc =
		ceph_sb_to_client(ci->vfs_inode.i_sb)->mdsc;
	int removed = 0;

	dout("__ceph_remove_cap %p from %p\n", cap, &ci->vfs_inode);

	/* remove from inode's cap rbtree, and clear auth cap */
	rb_erase(&cap->ci_node, &ci->i_caps);
	if (ci->i_auth_cap == cap)
		ci->i_auth_cap = NULL;

	/* remove from session list */
	spin_lock(&session->s_cap_lock);
	if (session->s_cap_iterator == cap) {
		/* not yet, we are iterating over this very cap */
		dout("__ceph_remove_cap  delaying %p removal from session %p\n",
		     cap, cap->session);
	} else {
		list_del_init(&cap->session_caps);
		session->s_nr_caps--;
		cap->session = NULL;
		removed = 1;
	}
	/* protect backpointer with s_cap_lock: see iterate_session_caps */
	cap->ci = NULL;

	/*
	 * s_cap_reconnect is protected by s_cap_lock. no one changes
	 * s_cap_gen while session is in the reconnect state.
	 */
	if (queue_release &&
	    (!session->s_cap_reconnect || cap->cap_gen == session->s_cap_gen)) {
		cap->queue_release = 1;
		if (removed) {
			__ceph_queue_cap_release(session, cap);
			removed = 0;
		}
	} else {
		cap->queue_release = 0;
	}
	cap->cap_ino = ci->i_vino.ino;

	spin_unlock(&session->s_cap_lock);

	if (removed)
		ceph_put_cap(mdsc, cap);

	/* when reconnect denied, we remove session caps forcibly,
	 * i_wr_ref can be non-zero. If there are ongoing write,
	 * keep i_snap_realm.
	 */
	if (!__ceph_is_any_caps(ci) && ci->i_wr_ref == 0 && ci->i_snap_realm)
		drop_inode_snap_realm(ci);

	if (!__ceph_is_any_real_caps(ci))
		__cap_delay_cancel(mdsc, ci);
}