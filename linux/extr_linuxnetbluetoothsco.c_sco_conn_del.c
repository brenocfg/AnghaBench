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
struct sock {int dummy; } ;
struct sco_conn {struct sock* sk; } ;
struct hci_conn {struct sco_conn* sco_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,struct sco_conn*,int) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  kfree (struct sco_conn*) ; 
 int /*<<< orphan*/  sco_chan_del (struct sock*,int) ; 
 int /*<<< orphan*/  sco_conn_lock (struct sco_conn*) ; 
 int /*<<< orphan*/  sco_conn_unlock (struct sco_conn*) ; 
 int /*<<< orphan*/  sco_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  sco_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void sco_conn_del(struct hci_conn *hcon, int err)
{
	struct sco_conn *conn = hcon->sco_data;
	struct sock *sk;

	if (!conn)
		return;

	BT_DBG("hcon %p conn %p, err %d", hcon, conn, err);

	/* Kill socket */
	sco_conn_lock(conn);
	sk = conn->sk;
	sco_conn_unlock(conn);

	if (sk) {
		sock_hold(sk);
		bh_lock_sock(sk);
		sco_sock_clear_timer(sk);
		sco_chan_del(sk, err);
		bh_unlock_sock(sk);
		sco_sock_kill(sk);
		sock_put(sk);
	}

	hcon->sco_data = NULL;
	kfree(conn);
}