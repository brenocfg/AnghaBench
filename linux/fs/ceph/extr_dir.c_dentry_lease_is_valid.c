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
typedef  int /*<<< orphan*/  u32 ;
struct dentry {int /*<<< orphan*/  d_lock; } ;
struct ceph_mds_session {int dummy; } ;
struct ceph_dentry_info {int /*<<< orphan*/  lease_renew_from; scalar_t__ lease_renew_after; int /*<<< orphan*/  lease_seq; int /*<<< orphan*/  lease_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MDS_LEASE_RENEW ; 
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 scalar_t__ __dentry_lease_is_valid (struct ceph_dentry_info*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 struct ceph_mds_session* ceph_get_mds_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_mdsc_lease_send_msg (struct ceph_mds_session*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dentry_lease_is_valid(struct dentry *dentry, unsigned int flags)
{
	struct ceph_dentry_info *di;
	struct ceph_mds_session *session = NULL;
	u32 seq = 0;
	int valid = 0;

	spin_lock(&dentry->d_lock);
	di = ceph_dentry(dentry);
	if (di && __dentry_lease_is_valid(di)) {
		valid = 1;

		if (di->lease_renew_after &&
		    time_after(jiffies, di->lease_renew_after)) {
			/*
			 * We should renew. If we're in RCU walk mode
			 * though, we can't do that so just return
			 * -ECHILD.
			 */
			if (flags & LOOKUP_RCU) {
				valid = -ECHILD;
			} else {
				session = ceph_get_mds_session(di->lease_session);
				seq = di->lease_seq;
				di->lease_renew_after = 0;
				di->lease_renew_from = jiffies;
			}
		}
	}
	spin_unlock(&dentry->d_lock);

	if (session) {
		ceph_mdsc_lease_send_msg(session, dentry,
					 CEPH_MDS_LEASE_RENEW, seq);
		ceph_put_mds_session(session);
	}
	dout("dentry_lease_is_valid - dentry %p = %d\n", dentry, valid);
	return valid;
}