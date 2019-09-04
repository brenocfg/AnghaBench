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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_msg {int dummy; } ;
struct ceph_mds_session {int /*<<< orphan*/  s_con; int /*<<< orphan*/  s_state; int /*<<< orphan*/  s_mds; } ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_SESSION_FLUSHMSG_ACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ceph_con_send (int /*<<< orphan*/ *,struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_session_state_name (int /*<<< orphan*/ ) ; 
 struct ceph_msg* create_session_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_flushmsg_ack(struct ceph_mds_client *mdsc,
			     struct ceph_mds_session *session, u64 seq)
{
	struct ceph_msg *msg;

	dout("send_flushmsg_ack to mds%d (%s)s seq %lld\n",
	     session->s_mds, ceph_session_state_name(session->s_state), seq);
	msg = create_session_msg(CEPH_SESSION_FLUSHMSG_ACK, seq);
	if (!msg)
		return -ENOMEM;
	ceph_con_send(&session->s_con, msg);
	return 0;
}