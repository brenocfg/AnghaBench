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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct ceph_mds_session {scalar_t__ s_cap_gen; } ;
struct ceph_mds_reply_lease {int /*<<< orphan*/  seq; int /*<<< orphan*/  duration_ms; } ;
struct ceph_dentry_info {scalar_t__ lease_gen; unsigned long time; unsigned long lease_renew_after; scalar_t__ lease_renew_from; void* lease_seq; struct ceph_mds_session* lease_session; int /*<<< orphan*/  lease_shared_gen; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_shared_gen; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  __ceph_dentry_dir_lease_touch (struct ceph_dentry_info*) ; 
 int /*<<< orphan*/  __ceph_dentry_lease_touch (struct ceph_dentry_info*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 struct ceph_mds_session* ceph_get_mds_session (struct ceph_mds_session*) ; 
 TYPE_1__* ceph_inode (struct inode*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,unsigned long,unsigned long) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void __update_dentry_lease(struct inode *dir, struct dentry *dentry,
				  struct ceph_mds_reply_lease *lease,
				  struct ceph_mds_session *session,
				  unsigned long from_time,
				  struct ceph_mds_session **old_lease_session)
{
	struct ceph_dentry_info *di = ceph_dentry(dentry);
	long unsigned duration = le32_to_cpu(lease->duration_ms);
	long unsigned ttl = from_time + (duration * HZ) / 1000;
	long unsigned half_ttl = from_time + (duration * HZ / 2) / 1000;

	dout("update_dentry_lease %p duration %lu ms ttl %lu\n",
	     dentry, duration, ttl);

	/* only track leases on regular dentries */
	if (ceph_snap(dir) != CEPH_NOSNAP)
		return;

	di->lease_shared_gen = atomic_read(&ceph_inode(dir)->i_shared_gen);
	if (duration == 0) {
		__ceph_dentry_dir_lease_touch(di);
		return;
	}

	if (di->lease_gen == session->s_cap_gen &&
	    time_before(ttl, di->time))
		return;  /* we already have a newer lease. */

	if (di->lease_session && di->lease_session != session) {
		*old_lease_session = di->lease_session;
		di->lease_session = NULL;
	}

	if (!di->lease_session)
		di->lease_session = ceph_get_mds_session(session);
	di->lease_gen = session->s_cap_gen;
	di->lease_seq = le32_to_cpu(lease->seq);
	di->lease_renew_after = half_ttl;
	di->lease_renew_from = 0;
	di->time = ttl;

	__ceph_dentry_lease_touch(di);
}