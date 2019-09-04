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
struct sock {int sk_state; int sk_err; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct l2cap_chan {int state; int /*<<< orphan*/  nesting; struct sock* data; } ;
struct TYPE_2__ {struct sock* parent; } ;

/* Variables and functions */
#define  BT_BOUND 131 
#define  BT_CLOSED 130 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int /*<<< orphan*/ ) ; 
#define  BT_LISTEN 129 
#define  BT_OPEN 128 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_accept_unlink (struct sock*) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_cleanup_listen (struct sock*) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_string (int) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static void l2cap_sock_teardown_cb(struct l2cap_chan *chan, int err)
{
	struct sock *sk = chan->data;
	struct sock *parent;

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	/* This callback can be called both for server (BT_LISTEN)
	 * sockets as well as "normal" ones. To avoid lockdep warnings
	 * with child socket locking (through l2cap_sock_cleanup_listen)
	 * we need separation into separate nesting levels. The simplest
	 * way to accomplish this is to inherit the nesting level used
	 * for the channel.
	 */
	lock_sock_nested(sk, atomic_read(&chan->nesting));

	parent = bt_sk(sk)->parent;

	sock_set_flag(sk, SOCK_ZAPPED);

	switch (chan->state) {
	case BT_OPEN:
	case BT_BOUND:
	case BT_CLOSED:
		break;
	case BT_LISTEN:
		l2cap_sock_cleanup_listen(sk);
		sk->sk_state = BT_CLOSED;
		chan->state = BT_CLOSED;

		break;
	default:
		sk->sk_state = BT_CLOSED;
		chan->state = BT_CLOSED;

		sk->sk_err = err;

		if (parent) {
			bt_accept_unlink(sk);
			parent->sk_data_ready(parent);
		} else {
			sk->sk_state_change(sk);
		}

		break;
	}

	release_sock(sk);
}