#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_4__ {struct ceph_mds_lease* iov_base; } ;
struct ceph_msg {int more_to_follow; TYPE_1__ front; } ;
struct ceph_mds_session {int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_mds; } ;
struct ceph_mds_lease {char action; int /*<<< orphan*/  seq; void* last; void* first; void* ino; } ;
struct TYPE_6__ {int /*<<< orphan*/  snap; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 char CEPH_MDS_LEASE_RELEASE ; 
 int /*<<< orphan*/  CEPH_MSG_CLIENT_LEASE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_lease_op_name (char) ; 
 struct ceph_msg* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ ceph_vino (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,struct ceph_mds_lease*) ; 

void ceph_mdsc_lease_send_msg(struct ceph_mds_session *session,
			      struct inode *inode,
			      struct dentry *dentry, char action,
			      u32 seq)
{
	struct ceph_msg *msg;
	struct ceph_mds_lease *lease;
	int len = sizeof(*lease) + sizeof(u32);
	int dnamelen = 0;

	dout("lease_send_msg inode %p dentry %p %s to mds%d\n",
	     inode, dentry, ceph_lease_op_name(action), session->s_mds);
	dnamelen = dentry->d_name.len;
	len += dnamelen;

	msg = ceph_msg_new(CEPH_MSG_CLIENT_LEASE, len, GFP_NOFS, false);
	if (!msg)
		return;
	lease = msg->front.iov_base;
	lease->action = action;
	lease->ino = cpu_to_le64(ceph_vino(inode).ino);
	lease->first = lease->last = cpu_to_le64(ceph_vino(inode).snap);
	lease->seq = cpu_to_le32(seq);
	put_unaligned_le32(dnamelen, lease + 1);
	memcpy((void *)(lease + 1) + 4, dentry->d_name.name, dnamelen);

	/*
	 * if this is a preemptive lease RELEASE, no need to
	 * flush request stream, since the actual request will
	 * soon follow.
	 */
	msg->more_to_follow = (action == CEPH_MDS_LEASE_RELEASE);

	ceph_con_send(&session->s_con, msg);
}