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
struct dentry {int /*<<< orphan*/  d_lock; struct dentry* d_parent; } ;
struct ceph_vino {int dummy; } ;
struct ceph_mds_session {scalar_t__ s_cap_gen; } ;
struct ceph_mds_reply_lease {int /*<<< orphan*/  seq; int /*<<< orphan*/  duration_ms; } ;
struct ceph_dentry_info {scalar_t__ lease_gen; unsigned long time; unsigned long lease_renew_after; scalar_t__ lease_renew_from; void* lease_seq; struct ceph_mds_session* lease_session; int /*<<< orphan*/  lease_shared_gen; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_shared_gen; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  ceph_dentry_lru_touch (struct dentry*) ; 
 struct ceph_mds_session* ceph_get_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_ino_compare (struct inode*,struct ceph_vino*) ; 
 TYPE_1__* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,unsigned long,unsigned long) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void update_dentry_lease(struct dentry *dentry,
				struct ceph_mds_reply_lease *lease,
				struct ceph_mds_session *session,
				unsigned long from_time,
				struct ceph_vino *tgt_vino,
				struct ceph_vino *dir_vino)
{
	struct ceph_dentry_info *di = ceph_dentry(dentry);
	long unsigned duration = le32_to_cpu(lease->duration_ms);
	long unsigned ttl = from_time + (duration * HZ) / 1000;
	long unsigned half_ttl = from_time + (duration * HZ / 2) / 1000;
	struct inode *dir;
	struct ceph_mds_session *old_lease_session = NULL;

	/*
	 * Make sure dentry's inode matches tgt_vino. NULL tgt_vino means that
	 * we expect a negative dentry.
	 */
	if (!tgt_vino && d_really_is_positive(dentry))
		return;

	if (tgt_vino && (d_really_is_negative(dentry) ||
			!ceph_ino_compare(d_inode(dentry), tgt_vino)))
		return;

	spin_lock(&dentry->d_lock);
	dout("update_dentry_lease %p duration %lu ms ttl %lu\n",
	     dentry, duration, ttl);

	dir = d_inode(dentry->d_parent);

	/* make sure parent matches dir_vino */
	if (!ceph_ino_compare(dir, dir_vino))
		goto out_unlock;

	/* only track leases on regular dentries */
	if (ceph_snap(dir) != CEPH_NOSNAP)
		goto out_unlock;

	di->lease_shared_gen = atomic_read(&ceph_inode(dir)->i_shared_gen);

	if (duration == 0)
		goto out_unlock;

	if (di->lease_gen == session->s_cap_gen &&
	    time_before(ttl, di->time))
		goto out_unlock;  /* we already have a newer lease. */

	if (di->lease_session && di->lease_session != session) {
		old_lease_session = di->lease_session;
		di->lease_session = NULL;
	}

	ceph_dentry_lru_touch(dentry);

	if (!di->lease_session)
		di->lease_session = ceph_get_mds_session(session);
	di->lease_gen = session->s_cap_gen;
	di->lease_seq = le32_to_cpu(lease->seq);
	di->lease_renew_after = half_ttl;
	di->lease_renew_from = 0;
	di->time = ttl;
out_unlock:
	spin_unlock(&dentry->d_lock);
	if (old_lease_session)
		ceph_put_mds_session(old_lease_session);
}