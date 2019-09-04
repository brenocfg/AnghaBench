#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;
struct msghdr {int msg_flags; } ;
struct l2cap_chan {int dummy; } ;
struct TYPE_2__ {struct l2cap_chan* chan; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int MSG_OOB ; 
 int bt_sock_wait_ready (struct sock*,int) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int l2cap_chan_send (struct l2cap_chan*,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int sock_error (struct sock*) ; 

__attribute__((used)) static int l2cap_sock_sendmsg(struct socket *sock, struct msghdr *msg,
			      size_t len)
{
	struct sock *sk = sock->sk;
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
	int err;

	BT_DBG("sock %p, sk %p", sock, sk);

	err = sock_error(sk);
	if (err)
		return err;

	if (msg->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	if (sk->sk_state != BT_CONNECTED)
		return -ENOTCONN;

	lock_sock(sk);
	err = bt_sock_wait_ready(sk, msg->msg_flags);
	release_sock(sk);
	if (err)
		return err;

	l2cap_chan_lock(chan);
	err = l2cap_chan_send(chan, msg, len);
	l2cap_chan_unlock(chan);

	return err;
}