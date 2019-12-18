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
struct inode {int dummy; } ;
struct ceph_vino {void* snap; void* ino; } ;
struct ceph_mds_session {int dummy; } ;
struct ceph_mds_reply_info_parsed {int dir_nr; struct ceph_mds_reply_dir_entry* dir_entries; } ;
struct ceph_mds_request {int /*<<< orphan*/  r_caps_reservation; int /*<<< orphan*/  r_request_started; TYPE_2__* r_dentry; struct ceph_mds_reply_info_parsed r_reply_info; } ;
struct TYPE_6__ {TYPE_1__* in; } ;
struct ceph_mds_reply_dir_entry {TYPE_3__ inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  snapid; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  ceph_async_iput (struct inode*) ; 
 struct inode* ceph_get_inode (int /*<<< orphan*/ ,struct ceph_vino) ; 
 int /*<<< orphan*/  dout (char*,int) ; 
 int fill_inode (struct inode*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,struct ceph_mds_session*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct inode*,int) ; 

__attribute__((used)) static int readdir_prepopulate_inodes_only(struct ceph_mds_request *req,
					   struct ceph_mds_session *session)
{
	struct ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
	int i, err = 0;

	for (i = 0; i < rinfo->dir_nr; i++) {
		struct ceph_mds_reply_dir_entry *rde = rinfo->dir_entries + i;
		struct ceph_vino vino;
		struct inode *in;
		int rc;

		vino.ino = le64_to_cpu(rde->inode.in->ino);
		vino.snap = le64_to_cpu(rde->inode.in->snapid);

		in = ceph_get_inode(req->r_dentry->d_sb, vino);
		if (IS_ERR(in)) {
			err = PTR_ERR(in);
			dout("new_inode badness got %d\n", err);
			continue;
		}
		rc = fill_inode(in, NULL, &rde->inode, NULL, session,
				req->r_request_started, -1,
				&req->r_caps_reservation);
		if (rc < 0) {
			pr_err("fill_inode badness on %p got %d\n", in, rc);
			err = rc;
		}
		/* avoid calling iput_final() in mds dispatch threads */
		ceph_async_iput(in);
	}

	return err;
}