#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ceph_mds_session {scalar_t__ s_state; int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_waiting; } ;
struct ceph_mds_request {int r_err; int r_resend_mds; scalar_t__ r_request_started; int /*<<< orphan*/  r_request; int /*<<< orphan*/  r_wait; int /*<<< orphan*/  r_session; scalar_t__ r_timeout; scalar_t__ r_started; int /*<<< orphan*/  r_req_flags; } ;
struct ceph_mds_client {int mdsmap_err; int /*<<< orphan*/  waiting_for_map; TYPE_3__* mdsmap; TYPE_2__* fsc; } ;
struct TYPE_7__ {scalar_t__ m_epoch; } ;
struct TYPE_6__ {TYPE_1__* mount_options; int /*<<< orphan*/  mount_state; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MDS_R_ABORTED ; 
 int /*<<< orphan*/  CEPH_MDS_R_GOT_RESULT ; 
 scalar_t__ CEPH_MDS_SESSION_CLOSING ; 
 scalar_t__ CEPH_MDS_SESSION_HUNG ; 
 scalar_t__ CEPH_MDS_SESSION_NEW ; 
 scalar_t__ CEPH_MDS_SESSION_OPEN ; 
 scalar_t__ CEPH_MDS_SESSION_REJECTED ; 
 scalar_t__ CEPH_MDS_STATE_ACTIVE ; 
 scalar_t__ CEPH_MOUNT_MOUNTING ; 
 int CEPH_MOUNT_OPT_MOUNTWAIT ; 
 scalar_t__ CEPH_MOUNT_SHUTDOWN ; 
 int EACCES ; 
 int EIO ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct ceph_mds_session*) ; 
 int PTR_ERR (struct ceph_mds_session*) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 struct ceph_mds_session* __ceph_lookup_mds_session (struct ceph_mds_client*,int) ; 
 int __choose_mds (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __open_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int __prepare_send_request (struct ceph_mds_client*,struct ceph_mds_request*,int,int) ; 
 int /*<<< orphan*/  __unregister_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_mdsmap_get_state (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ceph_mdsmap_is_cluster_available (TYPE_3__*) ; 
 int /*<<< orphan*/  ceph_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_session_state_name (scalar_t__) ; 
 int /*<<< orphan*/  complete_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  get_session (struct ceph_mds_session*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  put_request_session (struct ceph_mds_request*) ; 
 struct ceph_mds_session* register_session (struct ceph_mds_client*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void __do_request(struct ceph_mds_client *mdsc,
			struct ceph_mds_request *req)
{
	struct ceph_mds_session *session = NULL;
	int mds = -1;
	int err = 0;

	if (req->r_err || test_bit(CEPH_MDS_R_GOT_RESULT, &req->r_req_flags)) {
		if (test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags))
			__unregister_request(mdsc, req);
		return;
	}

	if (req->r_timeout &&
	    time_after_eq(jiffies, req->r_started + req->r_timeout)) {
		dout("do_request timed out\n");
		err = -EIO;
		goto finish;
	}
	if (READ_ONCE(mdsc->fsc->mount_state) == CEPH_MOUNT_SHUTDOWN) {
		dout("do_request forced umount\n");
		err = -EIO;
		goto finish;
	}
	if (READ_ONCE(mdsc->fsc->mount_state) == CEPH_MOUNT_MOUNTING) {
		if (mdsc->mdsmap_err) {
			err = mdsc->mdsmap_err;
			dout("do_request mdsmap err %d\n", err);
			goto finish;
		}
		if (mdsc->mdsmap->m_epoch == 0) {
			dout("do_request no mdsmap, waiting for map\n");
			list_add(&req->r_wait, &mdsc->waiting_for_map);
			return;
		}
		if (!(mdsc->fsc->mount_options->flags &
		      CEPH_MOUNT_OPT_MOUNTWAIT) &&
		    !ceph_mdsmap_is_cluster_available(mdsc->mdsmap)) {
			err = -ENOENT;
			pr_info("probably no mds server is up\n");
			goto finish;
		}
	}

	put_request_session(req);

	mds = __choose_mds(mdsc, req);
	if (mds < 0 ||
	    ceph_mdsmap_get_state(mdsc->mdsmap, mds) < CEPH_MDS_STATE_ACTIVE) {
		dout("do_request no mds or not active, waiting for map\n");
		list_add(&req->r_wait, &mdsc->waiting_for_map);
		return;
	}

	/* get, open session */
	session = __ceph_lookup_mds_session(mdsc, mds);
	if (!session) {
		session = register_session(mdsc, mds);
		if (IS_ERR(session)) {
			err = PTR_ERR(session);
			goto finish;
		}
	}
	req->r_session = get_session(session);

	dout("do_request mds%d session %p state %s\n", mds, session,
	     ceph_session_state_name(session->s_state));
	if (session->s_state != CEPH_MDS_SESSION_OPEN &&
	    session->s_state != CEPH_MDS_SESSION_HUNG) {
		if (session->s_state == CEPH_MDS_SESSION_REJECTED) {
			err = -EACCES;
			goto out_session;
		}
		if (session->s_state == CEPH_MDS_SESSION_NEW ||
		    session->s_state == CEPH_MDS_SESSION_CLOSING)
			__open_session(mdsc, session);
		list_add(&req->r_wait, &session->s_waiting);
		goto out_session;
	}

	/* send request */
	req->r_resend_mds = -1;   /* forget any previous mds hint */

	if (req->r_request_started == 0)   /* note request start time */
		req->r_request_started = jiffies;

	err = __prepare_send_request(mdsc, req, mds, false);
	if (!err) {
		ceph_msg_get(req->r_request);
		ceph_con_send(&session->s_con, req->r_request);
	}

out_session:
	ceph_put_mds_session(session);
finish:
	if (err) {
		dout("__do_request early error %d\n", err);
		req->r_err = err;
		complete_request(mdsc, req);
		__unregister_request(mdsc, req);
	}
	return;
}