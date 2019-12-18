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
struct ceph_mds_request {scalar_t__ r_tid; int r_err; scalar_t__ r_op; struct inode* r_unsafe_dir; int /*<<< orphan*/  r_gid; int /*<<< orphan*/  r_uid; scalar_t__ r_num_caps; int /*<<< orphan*/  r_caps_reservation; } ;
struct ceph_mds_client {scalar_t__ last_tid; scalar_t__ oldest_tid; int /*<<< orphan*/  request_tree; } ;

/* Variables and functions */
 scalar_t__ CEPH_MDS_OP_SETFILELOCK ; 
 int /*<<< orphan*/  ceph_mdsc_get_request (struct ceph_mds_request*) ; 
 int ceph_reserve_caps (struct ceph_mds_client*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_request*,scalar_t__) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  insert_request (int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  pr_err (char*,struct ceph_mds_request*,int) ; 

__attribute__((used)) static void __register_request(struct ceph_mds_client *mdsc,
			       struct ceph_mds_request *req,
			       struct inode *dir)
{
	int ret = 0;

	req->r_tid = ++mdsc->last_tid;
	if (req->r_num_caps) {
		ret = ceph_reserve_caps(mdsc, &req->r_caps_reservation,
					req->r_num_caps);
		if (ret < 0) {
			pr_err("__register_request %p "
			       "failed to reserve caps: %d\n", req, ret);
			/* set req->r_err to fail early from __do_request */
			req->r_err = ret;
			return;
		}
	}
	dout("__register_request %p tid %lld\n", req, req->r_tid);
	ceph_mdsc_get_request(req);
	insert_request(&mdsc->request_tree, req);

	req->r_uid = current_fsuid();
	req->r_gid = current_fsgid();

	if (mdsc->oldest_tid == 0 && req->r_op != CEPH_MDS_OP_SETFILELOCK)
		mdsc->oldest_tid = req->r_tid;

	if (dir) {
		ihold(dir);
		req->r_unsafe_dir = dir;
	}
}