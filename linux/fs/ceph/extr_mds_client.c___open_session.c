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
struct ceph_mds_session {int s_mds; int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_seq; int /*<<< orphan*/  s_renew_requested; int /*<<< orphan*/  s_state; } ;
struct ceph_mds_client {int /*<<< orphan*/  mdsmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MDS_SESSION_OPENING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_mds_state_name (int) ; 
 int ceph_mdsmap_get_state (int /*<<< orphan*/ ,int) ; 
 struct ceph_msg* create_session_open_msg (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int __open_session(struct ceph_mds_client *mdsc,
			  struct ceph_mds_session *session)
{
	struct ceph_msg *msg;
	int mstate;
	int mds = session->s_mds;

	/* wait for mds to go active? */
	mstate = ceph_mdsmap_get_state(mdsc->mdsmap, mds);
	dout("open_session to mds%d (%s)\n", mds,
	     ceph_mds_state_name(mstate));
	session->s_state = CEPH_MDS_SESSION_OPENING;
	session->s_renew_requested = jiffies;

	/* send connect message */
	msg = create_session_open_msg(mdsc, session->s_seq);
	if (!msg)
		return -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	return 0;
}