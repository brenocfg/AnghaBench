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
struct sock {int sk_err; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct sco_conn {scalar_t__ hcon; int /*<<< orphan*/ * sk; } ;
struct TYPE_2__ {struct sco_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,struct sco_conn*,int) ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  hci_conn_drop (scalar_t__) ; 
 int /*<<< orphan*/  sco_conn_lock (struct sco_conn*) ; 
 int /*<<< orphan*/  sco_conn_unlock (struct sco_conn*) ; 
 TYPE_1__* sco_pi (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void sco_chan_del(struct sock *sk, int err)
{
	struct sco_conn *conn;

	conn = sco_pi(sk)->conn;

	BT_DBG("sk %p, conn %p, err %d", sk, conn, err);

	if (conn) {
		sco_conn_lock(conn);
		conn->sk = NULL;
		sco_pi(sk)->conn = NULL;
		sco_conn_unlock(conn);

		if (conn->hcon)
			hci_conn_drop(conn->hcon);
	}

	sk->sk_state = BT_CLOSED;
	sk->sk_err   = err;
	sk->sk_state_change(sk);

	sock_set_flag(sk, SOCK_ZAPPED);
}