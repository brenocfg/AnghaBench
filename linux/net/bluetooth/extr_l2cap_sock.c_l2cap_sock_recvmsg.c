#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct msghdr {int dummy; } ;
struct l2cap_pinfo {TYPE_1__* chan; int /*<<< orphan*/ * rx_busy_skb; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ mode; int /*<<< orphan*/  conn_state; void* state; int /*<<< orphan*/  src_type; } ;

/* Variables and functions */
 void* BT_CONFIG ; 
 scalar_t__ BT_CONNECT2 ; 
 void* BT_CONNECTED ; 
 int /*<<< orphan*/  BT_SK_DEFER_SETUP ; 
 int /*<<< orphan*/  CONN_LOCAL_BUSY ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  __l2cap_connect_rsp_defer (TYPE_1__*) ; 
 int /*<<< orphan*/  __l2cap_le_connect_rsp_defer (TYPE_1__*) ; 
 int /*<<< orphan*/  __sock_queue_rcv_skb (struct sock*,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bdaddr_type_is_le (int /*<<< orphan*/ ) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int bt_sock_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 
 int bt_sock_stream_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 
 int /*<<< orphan*/  l2cap_chan_busy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_sock_recvmsg(struct socket *sock, struct msghdr *msg,
			      size_t len, int flags)
{
	struct sock *sk = sock->sk;
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	int err;

	lock_sock(sk);

	if (sk->sk_state == BT_CONNECT2 && test_bit(BT_SK_DEFER_SETUP,
						    &bt_sk(sk)->flags)) {
		if (bdaddr_type_is_le(pi->chan->src_type)) {
			sk->sk_state = BT_CONNECTED;
			pi->chan->state = BT_CONNECTED;
			__l2cap_le_connect_rsp_defer(pi->chan);
		} else {
			sk->sk_state = BT_CONFIG;
			pi->chan->state = BT_CONFIG;
			__l2cap_connect_rsp_defer(pi->chan);
		}

		err = 0;
		goto done;
	}

	release_sock(sk);

	if (sock->type == SOCK_STREAM)
		err = bt_sock_stream_recvmsg(sock, msg, len, flags);
	else
		err = bt_sock_recvmsg(sock, msg, len, flags);

	if (pi->chan->mode != L2CAP_MODE_ERTM)
		return err;

	/* Attempt to put pending rx data in the socket buffer */

	lock_sock(sk);

	if (!test_bit(CONN_LOCAL_BUSY, &pi->chan->conn_state))
		goto done;

	if (pi->rx_busy_skb) {
		if (!__sock_queue_rcv_skb(sk, pi->rx_busy_skb))
			pi->rx_busy_skb = NULL;
		else
			goto done;
	}

	/* Restore data flow when half of the receive buffer is
	 * available.  This avoids resending large numbers of
	 * frames.
	 */
	if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf >> 1)
		l2cap_chan_busy(pi->chan, 0);

done:
	release_sock(sk);
	return err;
}