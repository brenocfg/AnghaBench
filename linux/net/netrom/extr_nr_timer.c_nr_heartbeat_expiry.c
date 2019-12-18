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
struct timer_list {int dummy; } ;
struct sock {int sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  sk_state; } ;
struct nr_sock {int state; int condition; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; } ;

/* Variables and functions */
 int NR_COND_ACK_PENDING ; 
 int NR_COND_OWN_RX_BUSY ; 
 int /*<<< orphan*/  NR_INFOACK ; 
#define  NR_STATE_0 129 
#define  NR_STATE_3 128 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 int /*<<< orphan*/  TCP_LISTEN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_destroy_socket (struct sock*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  nr_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 struct sock* sk ; 
 int /*<<< orphan*/  sk_timer ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void nr_heartbeat_expiry(struct timer_list *t)
{
	struct sock *sk = from_timer(sk, t, sk_timer);
	struct nr_sock *nr = nr_sk(sk);

	bh_lock_sock(sk);
	switch (nr->state) {
	case NR_STATE_0:
		/* Magic here: If we listen() and a new link dies before it
		   is accepted() it isn't 'dead' so doesn't get removed. */
		if (sock_flag(sk, SOCK_DESTROY) ||
		    (sk->sk_state == TCP_LISTEN && sock_flag(sk, SOCK_DEAD))) {
			sock_hold(sk);
			bh_unlock_sock(sk);
			nr_destroy_socket(sk);
			sock_put(sk);
			return;
		}
		break;

	case NR_STATE_3:
		/*
		 * Check for the state of the receive buffer.
		 */
		if (atomic_read(&sk->sk_rmem_alloc) < (sk->sk_rcvbuf / 2) &&
		    (nr->condition & NR_COND_OWN_RX_BUSY)) {
			nr->condition &= ~NR_COND_OWN_RX_BUSY;
			nr->condition &= ~NR_COND_ACK_PENDING;
			nr->vl         = nr->vr;
			nr_write_internal(sk, NR_INFOACK);
			break;
		}
		break;
	}

	nr_start_heartbeat(sk);
	bh_unlock_sock(sk);
}