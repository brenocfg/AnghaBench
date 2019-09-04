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
typedef  int u32 ;
struct TYPE_4__ {int iov_len; struct ceph_mds_session_head* iov_base; } ;
struct ceph_msg {TYPE_2__ front; } ;
struct ceph_mds_session_head {int /*<<< orphan*/  max_caps; int /*<<< orphan*/  seq; int /*<<< orphan*/  op; } ;
struct ceph_mds_session {int s_mds; scalar_t__ s_state; int s_readonly; int /*<<< orphan*/  s_waiting; int /*<<< orphan*/  s_mutex; int /*<<< orphan*/  s_cap_lock; int /*<<< orphan*/  s_gen_ttl_lock; void* s_cap_ttl; int /*<<< orphan*/  s_cap_gen; int /*<<< orphan*/  s_renew_seq; void* s_ttl; struct ceph_mds_client* s_mdsc; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; int /*<<< orphan*/  session_close_wq; int /*<<< orphan*/  stopping; TYPE_1__* mdsmap; } ;
struct TYPE_3__ {int m_session_autoclose; } ;

/* Variables and functions */
 scalar_t__ CEPH_MDS_SESSION_HUNG ; 
 void* CEPH_MDS_SESSION_OPEN ; 
 scalar_t__ CEPH_MDS_SESSION_OPENING ; 
 scalar_t__ CEPH_MDS_SESSION_RECONNECTING ; 
 scalar_t__ CEPH_MDS_SESSION_REJECTED ; 
#define  CEPH_SESSION_CLOSE 135 
#define  CEPH_SESSION_FLUSHMSG 134 
#define  CEPH_SESSION_FORCE_RO 133 
#define  CEPH_SESSION_OPEN 132 
#define  CEPH_SESSION_RECALL_STATE 131 
#define  CEPH_SESSION_REJECT 130 
#define  CEPH_SESSION_RENEWCAPS 129 
#define  CEPH_SESSION_STALE 128 
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __close_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  __unregister_session (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  __wake_requests (struct ceph_mds_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_msg_dump (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_put_mds_session (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  ceph_session_op_name (int) ; 
 int /*<<< orphan*/  ceph_session_state_name (scalar_t__) ; 
 int /*<<< orphan*/  ceph_trim_caps (struct ceph_mds_client*,struct ceph_mds_session*,int) ; 
 int /*<<< orphan*/  cleanup_session_requests (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  get_session (struct ceph_mds_session*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kick_requests (struct ceph_mds_client*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  remove_session_caps (struct ceph_mds_session*) ; 
 int /*<<< orphan*/  renewed_caps (struct ceph_mds_client*,struct ceph_mds_session*,int) ; 
 int /*<<< orphan*/  send_flushmsg_ack (struct ceph_mds_client*,struct ceph_mds_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_renew_caps (struct ceph_mds_client*,struct ceph_mds_session*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_session_caps (struct ceph_mds_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_session(struct ceph_mds_session *session,
			   struct ceph_msg *msg)
{
	struct ceph_mds_client *mdsc = session->s_mdsc;
	u32 op;
	u64 seq;
	int mds = session->s_mds;
	struct ceph_mds_session_head *h = msg->front.iov_base;
	int wake = 0;

	/* decode */
	if (msg->front.iov_len < sizeof(*h))
		goto bad;
	op = le32_to_cpu(h->op);
	seq = le64_to_cpu(h->seq);

	mutex_lock(&mdsc->mutex);
	if (op == CEPH_SESSION_CLOSE) {
		get_session(session);
		__unregister_session(mdsc, session);
	}
	/* FIXME: this ttl calculation is generous */
	session->s_ttl = jiffies + HZ*mdsc->mdsmap->m_session_autoclose;
	mutex_unlock(&mdsc->mutex);

	mutex_lock(&session->s_mutex);

	dout("handle_session mds%d %s %p state %s seq %llu\n",
	     mds, ceph_session_op_name(op), session,
	     ceph_session_state_name(session->s_state), seq);

	if (session->s_state == CEPH_MDS_SESSION_HUNG) {
		session->s_state = CEPH_MDS_SESSION_OPEN;
		pr_info("mds%d came back\n", session->s_mds);
	}

	switch (op) {
	case CEPH_SESSION_OPEN:
		if (session->s_state == CEPH_MDS_SESSION_RECONNECTING)
			pr_info("mds%d reconnect success\n", session->s_mds);
		session->s_state = CEPH_MDS_SESSION_OPEN;
		renewed_caps(mdsc, session, 0);
		wake = 1;
		if (mdsc->stopping)
			__close_session(mdsc, session);
		break;

	case CEPH_SESSION_RENEWCAPS:
		if (session->s_renew_seq == seq)
			renewed_caps(mdsc, session, 1);
		break;

	case CEPH_SESSION_CLOSE:
		if (session->s_state == CEPH_MDS_SESSION_RECONNECTING)
			pr_info("mds%d reconnect denied\n", session->s_mds);
		cleanup_session_requests(mdsc, session);
		remove_session_caps(session);
		wake = 2; /* for good measure */
		wake_up_all(&mdsc->session_close_wq);
		break;

	case CEPH_SESSION_STALE:
		pr_info("mds%d caps went stale, renewing\n",
			session->s_mds);
		spin_lock(&session->s_gen_ttl_lock);
		session->s_cap_gen++;
		session->s_cap_ttl = jiffies - 1;
		spin_unlock(&session->s_gen_ttl_lock);
		send_renew_caps(mdsc, session);
		break;

	case CEPH_SESSION_RECALL_STATE:
		ceph_trim_caps(mdsc, session, le32_to_cpu(h->max_caps));
		break;

	case CEPH_SESSION_FLUSHMSG:
		send_flushmsg_ack(mdsc, session, seq);
		break;

	case CEPH_SESSION_FORCE_RO:
		dout("force_session_readonly %p\n", session);
		spin_lock(&session->s_cap_lock);
		session->s_readonly = true;
		spin_unlock(&session->s_cap_lock);
		wake_up_session_caps(session, 0);
		break;

	case CEPH_SESSION_REJECT:
		WARN_ON(session->s_state != CEPH_MDS_SESSION_OPENING);
		pr_info("mds%d rejected session\n", session->s_mds);
		session->s_state = CEPH_MDS_SESSION_REJECTED;
		cleanup_session_requests(mdsc, session);
		remove_session_caps(session);
		wake = 2; /* for good measure */
		break;

	default:
		pr_err("mdsc_handle_session bad op %d mds%d\n", op, mds);
		WARN_ON(1);
	}

	mutex_unlock(&session->s_mutex);
	if (wake) {
		mutex_lock(&mdsc->mutex);
		__wake_requests(mdsc, &session->s_waiting);
		if (wake == 2)
			kick_requests(mdsc, mds);
		mutex_unlock(&mdsc->mutex);
	}
	if (op == CEPH_SESSION_CLOSE)
		ceph_put_mds_session(session);
	return;

bad:
	pr_err("mdsc_handle_session corrupt message mds%d len %d\n", mds,
	       (int)msg->front.iov_len);
	ceph_msg_dump(msg);
	return;
}