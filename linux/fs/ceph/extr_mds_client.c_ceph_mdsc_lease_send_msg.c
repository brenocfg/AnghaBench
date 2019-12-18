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
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_2__ d_name; int /*<<< orphan*/  d_parent; } ;
struct TYPE_3__ {struct ceph_mds_lease* iov_base; } ;
struct ceph_msg {int more_to_follow; TYPE_1__ front; } ;
struct ceph_mds_session {int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_mds; } ;
struct ceph_mds_lease {char action; void* last; void* first; void* ino; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 char CEPH_MDS_LEASE_RELEASE ; 
 int /*<<< orphan*/  CEPH_MSG_CLIENT_LEASE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int NAME_MAX ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 int /*<<< orphan*/  ceph_lease_op_name (char) ; 
 struct ceph_msg* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,struct ceph_mds_lease*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_mdsc_lease_send_msg(struct ceph_mds_session *session,
			      struct dentry *dentry, char action,
			      u32 seq)
{
	struct ceph_msg *msg;
	struct ceph_mds_lease *lease;
	struct inode *dir;
	int len = sizeof(*lease) + sizeof(u32) + NAME_MAX;

	dout("lease_send_msg identry %p %s to mds%d\n",
	     dentry, ceph_lease_op_name(action), session->s_mds);

	msg = ceph_msg_new(CEPH_MSG_CLIENT_LEASE, len, GFP_NOFS, false);
	if (!msg)
		return;
	lease = msg->front.iov_base;
	lease->action = action;
	lease->seq = cpu_to_le32(seq);

	spin_lock(&dentry->d_lock);
	dir = d_inode(dentry->d_parent);
	lease->ino = cpu_to_le64(ceph_ino(dir));
	lease->first = lease->last = cpu_to_le64(ceph_snap(dir));

	put_unaligned_le32(dentry->d_name.len, lease + 1);
	memcpy((void *)(lease + 1) + 4,
	       dentry->d_name.name, dentry->d_name.len);
	spin_unlock(&dentry->d_lock);
	/*
	 * if this is a preemptive lease RELEASE, no need to
	 * flush request stream, since the actual request will
	 * soon follow.
	 */
	msg->more_to_follow = (action == CEPH_MDS_LEASE_RELEASE);

	ceph_con_send(&session->s_con, msg);
}