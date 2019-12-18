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
struct timer_list {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 int /*<<< orphan*/  TCP_LISTEN ; 
#define  X25_STATE_0 129 
#define  X25_STATE_3 128 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sock* sk ; 
 int /*<<< orphan*/  sk_timer ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  x25_check_rbuf (struct sock*) ; 
 int /*<<< orphan*/  x25_destroy_socket_from_timer (struct sock*) ; 
 TYPE_1__* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_start_heartbeat (struct sock*) ; 

__attribute__((used)) static void x25_heartbeat_expiry(struct timer_list *t)
{
	struct sock *sk = from_timer(sk, t, sk_timer);

	bh_lock_sock(sk);
	if (sock_owned_by_user(sk)) /* can currently only occur in state 3 */
		goto restart_heartbeat;

	switch (x25_sk(sk)->state) {

		case X25_STATE_0:
			/*
			 * Magic here: If we listen() and a new link dies
			 * before it is accepted() it isn't 'dead' so doesn't
			 * get removed.
			 */
			if (sock_flag(sk, SOCK_DESTROY) ||
			    (sk->sk_state == TCP_LISTEN &&
			     sock_flag(sk, SOCK_DEAD))) {
				bh_unlock_sock(sk);
				x25_destroy_socket_from_timer(sk);
				return;
			}
			break;

		case X25_STATE_3:
			/*
			 * Check for the state of the receive buffer.
			 */
			x25_check_rbuf(sk);
			break;
	}
restart_heartbeat:
	x25_start_heartbeat(sk);
	bh_unlock_sock(sk);
}