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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int iov_len; void* iov_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;
struct ceph_msg {TYPE_2__ front; TYPE_1__ hdr; } ;
struct ceph_mds_session {int dummy; } ;
struct ceph_mds_request {scalar_t__ r_num_fwd; scalar_t__ r_resend_mds; scalar_t__ r_attempts; int /*<<< orphan*/  r_req_flags; scalar_t__ r_err; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int /*<<< orphan*/  CEPH_MDS_R_ABORTED ; 
 int /*<<< orphan*/  CEPH_MDS_R_GOT_RESULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  __do_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __unregister_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  bad ; 
 scalar_t__ ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ceph_mds_request* lookup_get_request (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  put_request_session (struct ceph_mds_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_forward(struct ceph_mds_client *mdsc,
			   struct ceph_mds_session *session,
			   struct ceph_msg *msg)
{
	struct ceph_mds_request *req;
	u64 tid = le64_to_cpu(msg->hdr.tid);
	u32 next_mds;
	u32 fwd_seq;
	int err = -EINVAL;
	void *p = msg->front.iov_base;
	void *end = p + msg->front.iov_len;

	ceph_decode_need(&p, end, 2*sizeof(u32), bad);
	next_mds = ceph_decode_32(&p);
	fwd_seq = ceph_decode_32(&p);

	mutex_lock(&mdsc->mutex);
	req = lookup_get_request(mdsc, tid);
	if (!req) {
		dout("forward tid %llu to mds%d - req dne\n", tid, next_mds);
		goto out;  /* dup reply? */
	}

	if (test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags)) {
		dout("forward tid %llu aborted, unregistering\n", tid);
		__unregister_request(mdsc, req);
	} else if (fwd_seq <= req->r_num_fwd) {
		dout("forward tid %llu to mds%d - old seq %d <= %d\n",
		     tid, next_mds, req->r_num_fwd, fwd_seq);
	} else {
		/* resend. forward race not possible; mds would drop */
		dout("forward tid %llu to mds%d (we resend)\n", tid, next_mds);
		BUG_ON(req->r_err);
		BUG_ON(test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags));
		req->r_attempts = 0;
		req->r_num_fwd = fwd_seq;
		req->r_resend_mds = next_mds;
		put_request_session(req);
		__do_request(mdsc, req);
	}
	ceph_mdsc_put_request(req);
out:
	mutex_unlock(&mdsc->mutex);
	return;

bad:
	pr_err("mdsc_handle_forward decode error err=%d\n", err);
}