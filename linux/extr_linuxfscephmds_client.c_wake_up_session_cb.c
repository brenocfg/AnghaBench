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
struct inode {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_cap_wq; int /*<<< orphan*/  i_ceph_lock; scalar_t__ i_requested_max_size; scalar_t__ i_wanted_max_size; } ;
struct ceph_cap {int dummy; } ;

/* Variables and functions */
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wake_up_session_cb(struct inode *inode, struct ceph_cap *cap,
			      void *arg)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	if (arg) {
		spin_lock(&ci->i_ceph_lock);
		ci->i_wanted_max_size = 0;
		ci->i_requested_max_size = 0;
		spin_unlock(&ci->i_ceph_lock);
	}
	wake_up_all(&ci->i_cap_wq);
	return 0;
}