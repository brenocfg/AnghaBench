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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct qstr {int len; void* name; int /*<<< orphan*/  hash; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_lock; } ;
struct ceph_vino {struct inode* ino; int /*<<< orphan*/  snap; } ;
struct TYPE_4__ {int iov_len; struct ceph_mds_lease* iov_base; } ;
struct ceph_msg {TYPE_2__ front; } ;
struct ceph_mds_session {int s_mds; int /*<<< orphan*/  s_mutex; int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_cap_gen; int /*<<< orphan*/  s_seq; } ;
struct ceph_mds_lease {int action; int /*<<< orphan*/  duration_ms; int /*<<< orphan*/  seq; int /*<<< orphan*/  ino; } ;
struct ceph_mds_client {TYPE_1__* fsc; } ;
struct ceph_dentry_info {int /*<<< orphan*/  lease_renew_from; int /*<<< orphan*/  lease_renew_after; int /*<<< orphan*/  time; int /*<<< orphan*/  lease_seq; int /*<<< orphan*/  lease_gen; struct ceph_mds_session* lease_session; } ;
struct TYPE_3__ {struct super_block* sb; } ;

/* Variables and functions */
#define  CEPH_MDS_LEASE_RENEW 129 
#define  CEPH_MDS_LEASE_REVOKE 128 
 int CEPH_MDS_LEASE_REVOKE_ACK ; 
 int /*<<< orphan*/  CEPH_NOSNAP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ceph_mdsc_drop_dentry_lease (struct dentry*) ; 
 int /*<<< orphan*/  ceph_async_iput (struct inode*) ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 struct inode* ceph_find_inode (struct super_block*,struct ceph_vino) ; 
 int /*<<< orphan*/  ceph_lease_op_name (int) ; 
 int /*<<< orphan*/  ceph_msg_dump (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_get (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_seq_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dout (char*,int,...) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (struct dentry*,void*,int) ; 
 int get_unaligned_le32 (struct ceph_mds_lease*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct inode* le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_lease(struct ceph_mds_client *mdsc,
			 struct ceph_mds_session *session,
			 struct ceph_msg *msg)
{
	struct super_block *sb = mdsc->fsc->sb;
	struct inode *inode;
	struct dentry *parent, *dentry;
	struct ceph_dentry_info *di;
	int mds = session->s_mds;
	struct ceph_mds_lease *h = msg->front.iov_base;
	u32 seq;
	struct ceph_vino vino;
	struct qstr dname;
	int release = 0;

	dout("handle_lease from mds%d\n", mds);

	/* decode */
	if (msg->front.iov_len < sizeof(*h) + sizeof(u32))
		goto bad;
	vino.ino = le64_to_cpu(h->ino);
	vino.snap = CEPH_NOSNAP;
	seq = le32_to_cpu(h->seq);
	dname.len = get_unaligned_le32(h + 1);
	if (msg->front.iov_len < sizeof(*h) + sizeof(u32) + dname.len)
		goto bad;
	dname.name = (void *)(h + 1) + sizeof(u32);

	/* lookup inode */
	inode = ceph_find_inode(sb, vino);
	dout("handle_lease %s, ino %llx %p %.*s\n",
	     ceph_lease_op_name(h->action), vino.ino, inode,
	     dname.len, dname.name);

	mutex_lock(&session->s_mutex);
	session->s_seq++;

	if (!inode) {
		dout("handle_lease no inode %llx\n", vino.ino);
		goto release;
	}

	/* dentry */
	parent = d_find_alias(inode);
	if (!parent) {
		dout("no parent dentry on inode %p\n", inode);
		WARN_ON(1);
		goto release;  /* hrm... */
	}
	dname.hash = full_name_hash(parent, dname.name, dname.len);
	dentry = d_lookup(parent, &dname);
	dput(parent);
	if (!dentry)
		goto release;

	spin_lock(&dentry->d_lock);
	di = ceph_dentry(dentry);
	switch (h->action) {
	case CEPH_MDS_LEASE_REVOKE:
		if (di->lease_session == session) {
			if (ceph_seq_cmp(di->lease_seq, seq) > 0)
				h->seq = cpu_to_le32(di->lease_seq);
			__ceph_mdsc_drop_dentry_lease(dentry);
		}
		release = 1;
		break;

	case CEPH_MDS_LEASE_RENEW:
		if (di->lease_session == session &&
		    di->lease_gen == session->s_cap_gen &&
		    di->lease_renew_from &&
		    di->lease_renew_after == 0) {
			unsigned long duration =
				msecs_to_jiffies(le32_to_cpu(h->duration_ms));

			di->lease_seq = seq;
			di->time = di->lease_renew_from + duration;
			di->lease_renew_after = di->lease_renew_from +
				(duration >> 1);
			di->lease_renew_from = 0;
		}
		break;
	}
	spin_unlock(&dentry->d_lock);
	dput(dentry);

	if (!release)
		goto out;

release:
	/* let's just reuse the same message */
	h->action = CEPH_MDS_LEASE_REVOKE_ACK;
	ceph_msg_get(msg);
	ceph_con_send(&session->s_con, msg);

out:
	mutex_unlock(&session->s_mutex);
	/* avoid calling iput_final() in mds dispatch threads */
	ceph_async_iput(inode);
	return;

bad:
	pr_err("corrupt lease message\n");
	ceph_msg_dump(msg);
}