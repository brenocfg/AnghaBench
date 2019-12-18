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
struct sock {int sk_state; unsigned long sk_lingertime; scalar_t__ sk_bound_dev_if; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_err; } ;
struct iucv_sock {int /*<<< orphan*/ * hs_dev; int /*<<< orphan*/  backlog_skb_q; int /*<<< orphan*/  send_skb_q; int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IUCV_FLAG_FIN ; 
 int /*<<< orphan*/  AF_IUCV_TRANS_HIPER ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int IUCV_CLOSED ; 
#define  IUCV_CLOSING 131 
#define  IUCV_CONNECTED 130 
#define  IUCV_DISCONN 129 
 unsigned long IUCV_DISCONN_TIMEOUT ; 
#define  IUCV_LISTEN 128 
 int /*<<< orphan*/  SOCK_LINGER ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int iucv_send_ctrl (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_sever_path (struct sock*,int) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_cleanup_listen (struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_in_state (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_sock_wait (struct sock*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 
 int /*<<< orphan*/  stub4 (struct sock*) ; 

__attribute__((used)) static void iucv_sock_close(struct sock *sk)
{
	struct iucv_sock *iucv = iucv_sk(sk);
	unsigned long timeo;
	int err = 0;

	lock_sock(sk);

	switch (sk->sk_state) {
	case IUCV_LISTEN:
		iucv_sock_cleanup_listen(sk);
		break;

	case IUCV_CONNECTED:
		if (iucv->transport == AF_IUCV_TRANS_HIPER) {
			err = iucv_send_ctrl(sk, AF_IUCV_FLAG_FIN);
			sk->sk_state = IUCV_DISCONN;
			sk->sk_state_change(sk);
		}
		/* fall through */

	case IUCV_DISCONN:
		sk->sk_state = IUCV_CLOSING;
		sk->sk_state_change(sk);

		if (!err && !skb_queue_empty(&iucv->send_skb_q)) {
			if (sock_flag(sk, SOCK_LINGER) && sk->sk_lingertime)
				timeo = sk->sk_lingertime;
			else
				timeo = IUCV_DISCONN_TIMEOUT;
			iucv_sock_wait(sk,
					iucv_sock_in_state(sk, IUCV_CLOSED, 0),
					timeo);
		}
		/* fall through */

	case IUCV_CLOSING:
		sk->sk_state = IUCV_CLOSED;
		sk->sk_state_change(sk);

		sk->sk_err = ECONNRESET;
		sk->sk_state_change(sk);

		skb_queue_purge(&iucv->send_skb_q);
		skb_queue_purge(&iucv->backlog_skb_q);
		/* fall through */

	default:
		iucv_sever_path(sk, 1);
	}

	if (iucv->hs_dev) {
		dev_put(iucv->hs_dev);
		iucv->hs_dev = NULL;
		sk->sk_bound_dev_if = 0;
	}

	/* mark socket for deletion by iucv_sock_kill() */
	sock_set_flag(sk, SOCK_ZAPPED);

	release_sock(sk);
}