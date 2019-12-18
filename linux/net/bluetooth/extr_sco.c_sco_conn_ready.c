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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;void* sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sco_conn {TYPE_2__* hcon; struct sock* sk; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_SCO ; 
 void* BT_CONNECT2 ; 
 void* BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sco_conn*) ; 
 int /*<<< orphan*/  BT_SK_DEFER_SETUP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __sco_chan_add (struct sco_conn*,struct sock*,struct sock*) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_3__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  hci_conn_hold (TYPE_2__*) ; 
 int /*<<< orphan*/  sco_conn_lock (struct sco_conn*) ; 
 int /*<<< orphan*/  sco_conn_unlock (struct sco_conn*) ; 
 struct sock* sco_get_sock_listen (int /*<<< orphan*/ *) ; 
 TYPE_1__* sco_pi (struct sock*) ; 
 struct sock* sco_sock_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  sco_sock_init (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sco_conn_ready(struct sco_conn *conn)
{
	struct sock *parent;
	struct sock *sk = conn->sk;

	BT_DBG("conn %p", conn);

	if (sk) {
		sco_sock_clear_timer(sk);
		bh_lock_sock(sk);
		sk->sk_state = BT_CONNECTED;
		sk->sk_state_change(sk);
		bh_unlock_sock(sk);
	} else {
		sco_conn_lock(conn);

		if (!conn->hcon) {
			sco_conn_unlock(conn);
			return;
		}

		parent = sco_get_sock_listen(&conn->hcon->src);
		if (!parent) {
			sco_conn_unlock(conn);
			return;
		}

		bh_lock_sock(parent);

		sk = sco_sock_alloc(sock_net(parent), NULL,
				    BTPROTO_SCO, GFP_ATOMIC, 0);
		if (!sk) {
			bh_unlock_sock(parent);
			sco_conn_unlock(conn);
			return;
		}

		sco_sock_init(sk, parent);

		bacpy(&sco_pi(sk)->src, &conn->hcon->src);
		bacpy(&sco_pi(sk)->dst, &conn->hcon->dst);

		hci_conn_hold(conn->hcon);
		__sco_chan_add(conn, sk, parent);

		if (test_bit(BT_SK_DEFER_SETUP, &bt_sk(parent)->flags))
			sk->sk_state = BT_CONNECT2;
		else
			sk->sk_state = BT_CONNECTED;

		/* Wake up parent */
		parent->sk_data_ready(parent);

		bh_unlock_sock(parent);

		sco_conn_unlock(conn);
	}
}