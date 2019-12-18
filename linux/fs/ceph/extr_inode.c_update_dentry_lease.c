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
struct dentry {int /*<<< orphan*/  d_lock; } ;
struct ceph_mds_session {int dummy; } ;
struct ceph_mds_reply_lease {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __update_dentry_lease (struct inode*,struct dentry*,struct ceph_mds_reply_lease*,struct ceph_mds_session*,unsigned long,struct ceph_mds_session**) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void update_dentry_lease(struct inode *dir, struct dentry *dentry,
					struct ceph_mds_reply_lease *lease,
					struct ceph_mds_session *session,
					unsigned long from_time)
{
	struct ceph_mds_session *old_lease_session = NULL;
	spin_lock(&dentry->d_lock);
	__update_dentry_lease(dir, dentry, lease, session, from_time,
			      &old_lease_session);
	spin_unlock(&dentry->d_lock);
	if (old_lease_session)
		ceph_put_mds_session(old_lease_session);
}