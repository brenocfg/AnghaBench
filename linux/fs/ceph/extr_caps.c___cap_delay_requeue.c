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
struct ceph_mds_client {int /*<<< orphan*/  cap_delay_lock; int /*<<< orphan*/  cap_delay_list; int /*<<< orphan*/  stopping; } ;
struct ceph_inode_info {int i_ceph_flags; int /*<<< orphan*/  i_cap_delay_list; int /*<<< orphan*/  i_hold_caps_max; int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 int CEPH_I_FLUSH ; 
 int /*<<< orphan*/  __cap_set_timeouts (struct ceph_mds_client*,struct ceph_inode_info*) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cap_delay_requeue(struct ceph_mds_client *mdsc,
				struct ceph_inode_info *ci,
				bool set_timeout)
{
	dout("__cap_delay_requeue %p flags %d at %lu\n", &ci->vfs_inode,
	     ci->i_ceph_flags, ci->i_hold_caps_max);
	if (!mdsc->stopping) {
		spin_lock(&mdsc->cap_delay_lock);
		if (!list_empty(&ci->i_cap_delay_list)) {
			if (ci->i_ceph_flags & CEPH_I_FLUSH)
				goto no_change;
			list_del_init(&ci->i_cap_delay_list);
		}
		if (set_timeout)
			__cap_set_timeouts(mdsc, ci);
		list_add_tail(&ci->i_cap_delay_list, &mdsc->cap_delay_list);
no_change:
		spin_unlock(&mdsc->cap_delay_lock);
	}
}