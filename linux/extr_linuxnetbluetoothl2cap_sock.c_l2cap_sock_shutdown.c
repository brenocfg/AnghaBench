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
struct socket {struct sock* sk; } ;
struct sock {int sk_err; scalar_t__ sk_lingertime; scalar_t__ sk_shutdown; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_chan {scalar_t__ state; scalar_t__ mode; scalar_t__ unacked_frames; struct l2cap_conn* conn; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct l2cap_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLOSED ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
 int PF_EXITING ; 
 scalar_t__ SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_LINGER ; 
 int __l2cap_wait_ack (struct sock*,struct l2cap_chan*) ; 
 int bt_sock_wait_state (struct sock*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  l2cap_chan_close (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_hold (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_conn_get (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_conn_put (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  state_to_string (scalar_t__) ; 

__attribute__((used)) static int l2cap_sock_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	struct l2cap_chan *chan;
	struct l2cap_conn *conn;
	int err = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (!sk)
		return 0;

	lock_sock(sk);

	if (sk->sk_shutdown)
		goto shutdown_already;

	BT_DBG("Handling sock shutdown");

	/* prevent sk structure from being freed whilst unlocked */
	sock_hold(sk);

	chan = l2cap_pi(sk)->chan;
	/* prevent chan structure from being freed whilst unlocked */
	l2cap_chan_hold(chan);

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	if (chan->mode == L2CAP_MODE_ERTM &&
	    chan->unacked_frames > 0 &&
	    chan->state == BT_CONNECTED) {
		err = __l2cap_wait_ack(sk, chan);

		/* After waiting for ACKs, check whether shutdown
		 * has already been actioned to close the L2CAP
		 * link such as by l2cap_disconnection_req().
		 */
		if (sk->sk_shutdown)
			goto has_shutdown;
	}

	sk->sk_shutdown = SHUTDOWN_MASK;
	release_sock(sk);

	l2cap_chan_lock(chan);
	conn = chan->conn;
	if (conn)
		/* prevent conn structure from being freed */
		l2cap_conn_get(conn);
	l2cap_chan_unlock(chan);

	if (conn)
		/* mutex lock must be taken before l2cap_chan_lock() */
		mutex_lock(&conn->chan_lock);

	l2cap_chan_lock(chan);
	l2cap_chan_close(chan, 0);
	l2cap_chan_unlock(chan);

	if (conn) {
		mutex_unlock(&conn->chan_lock);
		l2cap_conn_put(conn);
	}

	lock_sock(sk);

	if (sock_flag(sk, SOCK_LINGER) && sk->sk_lingertime &&
	    !(current->flags & PF_EXITING))
		err = bt_sock_wait_state(sk, BT_CLOSED,
					 sk->sk_lingertime);

has_shutdown:
	l2cap_chan_put(chan);
	sock_put(sk);

shutdown_already:
	if (!err && sk->sk_err)
		err = -sk->sk_err;

	release_sock(sk);

	BT_DBG("Sock shutdown complete err: %d", err);

	return err;
}