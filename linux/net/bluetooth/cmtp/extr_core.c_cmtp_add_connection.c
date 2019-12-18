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
typedef  int u32 ;
struct socket {int /*<<< orphan*/  sk; } ;
struct cmtp_session {scalar_t__ state; int flags; struct socket* sock; int /*<<< orphan*/  terminate; int /*<<< orphan*/  task; int /*<<< orphan*/  num; int /*<<< orphan*/ ** reassembly; int /*<<< orphan*/  transmit; int /*<<< orphan*/  applications; int /*<<< orphan*/  msgnum; int /*<<< orphan*/  wait; int /*<<< orphan*/  name; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  mtu; } ;
struct cmtp_connadd_req {int flags; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  imtu; int /*<<< orphan*/  omtu; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  CMTP_INITIAL_MSGNUM ; 
 int /*<<< orphan*/  CMTP_LOOPBACK ; 
 int EBADFD ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct cmtp_session* __cmtp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cmtp_link_session (struct cmtp_session*) ; 
 int /*<<< orphan*/  __cmtp_unlink_session (struct cmtp_session*) ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cmtp_attach_device (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_session ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cmtp_session*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct cmtp_session*,char*,int /*<<< orphan*/ ) ; 
 struct cmtp_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_is_socket (struct socket*) ; 
 TYPE_2__* l2cap_pi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

int cmtp_add_connection(struct cmtp_connadd_req *req, struct socket *sock)
{
	u32 valid_flags = BIT(CMTP_LOOPBACK);
	struct cmtp_session *session, *s;
	int i, err;

	BT_DBG("");

	if (!l2cap_is_socket(sock))
		return -EBADFD;

	if (req->flags & ~valid_flags)
		return -EINVAL;

	session = kzalloc(sizeof(struct cmtp_session), GFP_KERNEL);
	if (!session)
		return -ENOMEM;

	down_write(&cmtp_session_sem);

	s = __cmtp_get_session(&l2cap_pi(sock->sk)->chan->dst);
	if (s && s->state == BT_CONNECTED) {
		err = -EEXIST;
		goto failed;
	}

	bacpy(&session->bdaddr, &l2cap_pi(sock->sk)->chan->dst);

	session->mtu = min_t(uint, l2cap_pi(sock->sk)->chan->omtu,
					l2cap_pi(sock->sk)->chan->imtu);

	BT_DBG("mtu %d", session->mtu);

	sprintf(session->name, "%pMR", &session->bdaddr);

	session->sock  = sock;
	session->state = BT_CONFIG;

	init_waitqueue_head(&session->wait);

	session->msgnum = CMTP_INITIAL_MSGNUM;

	INIT_LIST_HEAD(&session->applications);

	skb_queue_head_init(&session->transmit);

	for (i = 0; i < 16; i++)
		session->reassembly[i] = NULL;

	session->flags = req->flags;

	__cmtp_link_session(session);

	__module_get(THIS_MODULE);
	session->task = kthread_run(cmtp_session, session, "kcmtpd_ctr_%d",
								session->num);
	if (IS_ERR(session->task)) {
		module_put(THIS_MODULE);
		err = PTR_ERR(session->task);
		goto unlink;
	}

	if (!(session->flags & BIT(CMTP_LOOPBACK))) {
		err = cmtp_attach_device(session);
		if (err < 0) {
			atomic_inc(&session->terminate);
			wake_up_interruptible(sk_sleep(session->sock->sk));
			up_write(&cmtp_session_sem);
			return err;
		}
	}

	up_write(&cmtp_session_sem);
	return 0;

unlink:
	__cmtp_unlink_session(session);

failed:
	up_write(&cmtp_session_sem);
	kfree(session);
	return err;
}