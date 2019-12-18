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
struct socket {int /*<<< orphan*/  file; int /*<<< orphan*/  sk; } ;
struct l2cap_conn {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;
struct hidp_session {int flags; int /*<<< orphan*/  conn; struct socket* ctrl_sock; struct socket* intr_sock; int /*<<< orphan*/  report_queue; int /*<<< orphan*/  report_mutex; int /*<<< orphan*/  timer; int /*<<< orphan*/  dev_init; int /*<<< orphan*/  idle_to; void* intr_mtu; void* ctrl_mtu; int /*<<< orphan*/  intr_transmit; int /*<<< orphan*/  ctrl_transmit; TYPE_1__ user; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  state_queue; int /*<<< orphan*/  state; int /*<<< orphan*/  ref; } ;
struct hidp_connadd_req {int flags; int /*<<< orphan*/  idle_to; } ;
struct bt_sock {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_6__ {TYPE_2__* chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  imtu; int /*<<< orphan*/  omtu; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIDP_BLUETOOTH_VENDOR_ID ; 
 int /*<<< orphan*/  HIDP_SESSION_IDLING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct bt_sock* bt_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_idle_timeout ; 
 int hidp_session_dev_init (struct hidp_session*,struct hidp_connadd_req const*) ; 
 int /*<<< orphan*/  hidp_session_dev_work ; 
 int /*<<< orphan*/  hidp_session_probe ; 
 int /*<<< orphan*/  hidp_session_remove ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hidp_session*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct hidp_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_get (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_conn_put (int /*<<< orphan*/ ) ; 
 TYPE_3__* l2cap_pi (struct bt_sock*) ; 
 void* min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static int hidp_session_new(struct hidp_session **out, const bdaddr_t *bdaddr,
			    struct socket *ctrl_sock,
			    struct socket *intr_sock,
			    const struct hidp_connadd_req *req,
			    struct l2cap_conn *conn)
{
	struct hidp_session *session;
	int ret;
	struct bt_sock *ctrl, *intr;

	ctrl = bt_sk(ctrl_sock->sk);
	intr = bt_sk(intr_sock->sk);

	session = kzalloc(sizeof(*session), GFP_KERNEL);
	if (!session)
		return -ENOMEM;

	/* object and runtime management */
	kref_init(&session->ref);
	atomic_set(&session->state, HIDP_SESSION_IDLING);
	init_waitqueue_head(&session->state_queue);
	session->flags = req->flags & BIT(HIDP_BLUETOOTH_VENDOR_ID);

	/* connection management */
	bacpy(&session->bdaddr, bdaddr);
	session->conn = l2cap_conn_get(conn);
	session->user.probe = hidp_session_probe;
	session->user.remove = hidp_session_remove;
	INIT_LIST_HEAD(&session->user.list);
	session->ctrl_sock = ctrl_sock;
	session->intr_sock = intr_sock;
	skb_queue_head_init(&session->ctrl_transmit);
	skb_queue_head_init(&session->intr_transmit);
	session->ctrl_mtu = min_t(uint, l2cap_pi(ctrl)->chan->omtu,
					l2cap_pi(ctrl)->chan->imtu);
	session->intr_mtu = min_t(uint, l2cap_pi(intr)->chan->omtu,
					l2cap_pi(intr)->chan->imtu);
	session->idle_to = req->idle_to;

	/* device management */
	INIT_WORK(&session->dev_init, hidp_session_dev_work);
	timer_setup(&session->timer, hidp_idle_timeout, 0);

	/* session data */
	mutex_init(&session->report_mutex);
	init_waitqueue_head(&session->report_queue);

	ret = hidp_session_dev_init(session, req);
	if (ret)
		goto err_free;

	get_file(session->intr_sock->file);
	get_file(session->ctrl_sock->file);
	*out = session;
	return 0;

err_free:
	l2cap_conn_put(session->conn);
	kfree(session);
	return ret;
}