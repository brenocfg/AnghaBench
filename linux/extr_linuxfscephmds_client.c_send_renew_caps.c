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
struct ceph_msg {int dummy; } ;
struct ceph_mds_session {int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_renew_seq; int /*<<< orphan*/  s_mds; int /*<<< orphan*/  s_renew_requested; int /*<<< orphan*/  s_cap_ttl; } ;
struct ceph_mds_client {int /*<<< orphan*/  mdsmap; } ;

/* Variables and functions */
 int CEPH_MDS_STATE_RECONNECT ; 
 int /*<<< orphan*/  CEPH_SESSION_REQUEST_RENEWCAPS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_mds_state_name (int) ; 
 int ceph_mdsmap_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ceph_msg* create_session_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_renew_caps(struct ceph_mds_client *mdsc,
			   struct ceph_mds_session *session)
{
	struct ceph_msg *msg;
	int state;

	if (time_after_eq(jiffies, session->s_cap_ttl) &&
	    time_after_eq(session->s_cap_ttl, session->s_renew_requested))
		pr_info("mds%d caps stale\n", session->s_mds);
	session->s_renew_requested = jiffies;

	/* do not try to renew caps until a recovering mds has reconnected
	 * with its clients. */
	state = ceph_mdsmap_get_state(mdsc->mdsmap, session->s_mds);
	if (state < CEPH_MDS_STATE_RECONNECT) {
		dout("send_renew_caps ignoring mds%d (%s)\n",
		     session->s_mds, ceph_mds_state_name(state));
		return 0;
	}

	dout("send_renew_caps to mds%d (%s)\n", session->s_mds,
		ceph_mds_state_name(state));
	msg = create_session_msg(CEPH_SESSION_REQUEST_RENEWCAPS,
				 ++session->s_renew_seq);
	if (!msg)
		return -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	return 0;
}