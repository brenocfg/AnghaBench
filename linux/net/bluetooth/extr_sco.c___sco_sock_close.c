#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; int /*<<< orphan*/  sk_socket; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hcon; } ;
struct TYPE_4__ {TYPE_2__* conn; } ;

/* Variables and functions */
#define  BT_CONFIG 133 
#define  BT_CONNECT 132 
#define  BT_CONNECT2 131 
#define  BT_CONNECTED 130 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int,int /*<<< orphan*/ ) ; 
#define  BT_DISCONN 129 
#define  BT_LISTEN 128 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  SCO_DISCONN_TIMEOUT ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  hci_conn_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sco_chan_del (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_conn_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  sco_conn_unlock (TYPE_2__*) ; 
 TYPE_1__* sco_pi (struct sock*) ; 
 int /*<<< orphan*/  sco_sock_cleanup_listen (struct sock*) ; 
 int /*<<< orphan*/  sco_sock_set_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sco_sock_close(struct sock *sk)
{
	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	switch (sk->sk_state) {
	case BT_LISTEN:
		sco_sock_cleanup_listen(sk);
		break;

	case BT_CONNECTED:
	case BT_CONFIG:
		if (sco_pi(sk)->conn->hcon) {
			sk->sk_state = BT_DISCONN;
			sco_sock_set_timer(sk, SCO_DISCONN_TIMEOUT);
			sco_conn_lock(sco_pi(sk)->conn);
			hci_conn_drop(sco_pi(sk)->conn->hcon);
			sco_pi(sk)->conn->hcon = NULL;
			sco_conn_unlock(sco_pi(sk)->conn);
		} else
			sco_chan_del(sk, ECONNRESET);
		break;

	case BT_CONNECT2:
	case BT_CONNECT:
	case BT_DISCONN:
		sco_chan_del(sk, ECONNRESET);
		break;

	default:
		sock_set_flag(sk, SOCK_ZAPPED);
		break;
	}
}