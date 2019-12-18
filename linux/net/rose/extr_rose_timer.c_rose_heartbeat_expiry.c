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
struct rose_sock {int state; int condition; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; } ;

/* Variables and functions */
 int ROSE_COND_ACK_PENDING ; 
 int ROSE_COND_OWN_RX_BUSY ; 
 int /*<<< orphan*/  ROSE_RR ; 
#define  ROSE_STATE_0 129 
#define  ROSE_STATE_3 128 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 int /*<<< orphan*/  TCP_LISTEN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rose_destroy_socket (struct sock*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 struct sock* sk ; 
 int /*<<< orphan*/  sk_timer ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rose_heartbeat_expiry(struct timer_list *t)
{
	struct sock *sk = from_timer(sk, t, sk_timer);
	struct rose_sock *rose = rose_sk(sk);

	bh_lock_sock(sk);
	switch (rose->state) {
	case ROSE_STATE_0:
		/* Magic here: If we listen() and a new link dies before it
		   is accepted() it isn't 'dead' so doesn't get removed. */
		if (sock_flag(sk, SOCK_DESTROY) ||
		    (sk->sk_state == TCP_LISTEN && sock_flag(sk, SOCK_DEAD))) {
			bh_unlock_sock(sk);
			rose_destroy_socket(sk);
			return;
		}
		break;

	case ROSE_STATE_3:
		/*
		 * Check for the state of the receive buffer.
		 */
		if (atomic_read(&sk->sk_rmem_alloc) < (sk->sk_rcvbuf / 2) &&
		    (rose->condition & ROSE_COND_OWN_RX_BUSY)) {
			rose->condition &= ~ROSE_COND_OWN_RX_BUSY;
			rose->condition &= ~ROSE_COND_ACK_PENDING;
			rose->vl         = rose->vr;
			rose_write_internal(sk, ROSE_RR);
			rose_stop_timer(sk);	/* HB */
			break;
		}
		break;
	}

	rose_start_heartbeat(sk);
	bh_unlock_sock(sk);
}