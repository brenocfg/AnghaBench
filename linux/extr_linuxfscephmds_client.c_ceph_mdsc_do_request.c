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
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct ceph_mds_request {int r_err; int (* r_wait_for_completion ) (struct ceph_mds_client*,struct ceph_mds_request*) ;int r_op; scalar_t__ r_parent; int /*<<< orphan*/  r_fill_mutex; int /*<<< orphan*/  r_req_flags; struct ceph_mds_request* r_tid; TYPE_2__ r_reply_info; int /*<<< orphan*/  r_timeout; int /*<<< orphan*/  r_completion; scalar_t__ r_old_dentry_dir; scalar_t__ r_inode; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_PIN ; 
 int CEPH_MDS_OP_WRITE ; 
 int /*<<< orphan*/  CEPH_MDS_R_ABORTED ; 
 int /*<<< orphan*/  CEPH_MDS_R_GOT_RESULT ; 
 int EIO ; 
 int /*<<< orphan*/  __do_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __register_request (struct ceph_mds_client*,struct ceph_mds_request*,struct inode*) ; 
 int /*<<< orphan*/  ceph_get_cap_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_inode (scalar_t__) ; 
 int /*<<< orphan*/  ceph_invalidate_dir_request (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_timeout_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ceph_mdsc_do_request(struct ceph_mds_client *mdsc,
			 struct inode *dir,
			 struct ceph_mds_request *req)
{
	int err;

	dout("do_request on %p\n", req);

	/* take CAP_PIN refs for r_inode, r_parent, r_old_dentry */
	if (req->r_inode)
		ceph_get_cap_refs(ceph_inode(req->r_inode), CEPH_CAP_PIN);
	if (req->r_parent)
		ceph_get_cap_refs(ceph_inode(req->r_parent), CEPH_CAP_PIN);
	if (req->r_old_dentry_dir)
		ceph_get_cap_refs(ceph_inode(req->r_old_dentry_dir),
				  CEPH_CAP_PIN);

	/* issue */
	mutex_lock(&mdsc->mutex);
	__register_request(mdsc, req, dir);
	__do_request(mdsc, req);

	if (req->r_err) {
		err = req->r_err;
		goto out;
	}

	/* wait */
	mutex_unlock(&mdsc->mutex);
	dout("do_request waiting\n");
	if (!req->r_timeout && req->r_wait_for_completion) {
		err = req->r_wait_for_completion(mdsc, req);
	} else {
		long timeleft = wait_for_completion_killable_timeout(
					&req->r_completion,
					ceph_timeout_jiffies(req->r_timeout));
		if (timeleft > 0)
			err = 0;
		else if (!timeleft)
			err = -EIO;  /* timed out */
		else
			err = timeleft;  /* killed */
	}
	dout("do_request waited, got %d\n", err);
	mutex_lock(&mdsc->mutex);

	/* only abort if we didn't race with a real reply */
	if (test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags)) {
		err = le32_to_cpu(req->r_reply_info.head->result);
	} else if (err < 0) {
		dout("aborted request %lld with %d\n", req->r_tid, err);

		/*
		 * ensure we aren't running concurrently with
		 * ceph_fill_trace or ceph_readdir_prepopulate, which
		 * rely on locks (dir mutex) held by our caller.
		 */
		mutex_lock(&req->r_fill_mutex);
		req->r_err = err;
		set_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags);
		mutex_unlock(&req->r_fill_mutex);

		if (req->r_parent &&
		    (req->r_op & CEPH_MDS_OP_WRITE))
			ceph_invalidate_dir_request(req);
	} else {
		err = req->r_err;
	}

out:
	mutex_unlock(&mdsc->mutex);
	dout("do_request %p done, result %d\n", req, err);
	return err;
}