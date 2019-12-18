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
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_lock; struct dentry* d_parent; TYPE_1__ d_name; } ;
struct ceph_vino {int dummy; } ;
struct ceph_mds_session {int dummy; } ;
struct ceph_mds_reply_lease {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __update_dentry_lease (struct inode*,struct dentry*,struct ceph_mds_reply_lease*,struct ceph_mds_session*,unsigned long,struct ceph_mds_session**) ; 
 int /*<<< orphan*/  ceph_ino_compare (struct inode*,struct ceph_vino*) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_dentry_lease_careful(struct dentry *dentry,
					struct ceph_mds_reply_lease *lease,
					struct ceph_mds_session *session,
					unsigned long from_time,
					char *dname, u32 dname_len,
					struct ceph_vino *pdvino,
					struct ceph_vino *ptvino)

{
	struct inode *dir;
	struct ceph_mds_session *old_lease_session = NULL;

	spin_lock(&dentry->d_lock);
	/* make sure dentry's name matches target */
	if (dentry->d_name.len != dname_len ||
	    memcmp(dentry->d_name.name, dname, dname_len))
		goto out_unlock;

	dir = d_inode(dentry->d_parent);
	/* make sure parent matches dvino */
	if (!ceph_ino_compare(dir, pdvino))
		goto out_unlock;

	/* make sure dentry's inode matches target. NULL ptvino means that
	 * we expect a negative dentry */
	if (ptvino) {
		if (d_really_is_negative(dentry))
			goto out_unlock;
		if (!ceph_ino_compare(d_inode(dentry), ptvino))
			goto out_unlock;
	} else {
		if (d_really_is_positive(dentry))
			goto out_unlock;
	}

	__update_dentry_lease(dir, dentry, lease, session,
			      from_time, &old_lease_session);
out_unlock:
	spin_unlock(&dentry->d_lock);
	if (old_lease_session)
		ceph_put_mds_session(old_lease_session);
}