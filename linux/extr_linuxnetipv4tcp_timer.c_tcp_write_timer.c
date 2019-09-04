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
struct sock {int /*<<< orphan*/  sk_tsq_flags; } ;
struct TYPE_2__ {struct sock sk; } ;
struct inet_connection_sock {TYPE_1__ icsk_inet; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_WRITE_TIMER_DEFERRED ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct inet_connection_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* icsk ; 
 int /*<<< orphan*/  icsk_retransmit_timer ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_timer_handler (struct sock*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcp_write_timer(struct timer_list *t)
{
	struct inet_connection_sock *icsk =
			from_timer(icsk, t, icsk_retransmit_timer);
	struct sock *sk = &icsk->icsk_inet.sk;

	bh_lock_sock(sk);
	if (!sock_owned_by_user(sk)) {
		tcp_write_timer_handler(sk);
	} else {
		/* delegate our work to tcp_release_cb() */
		if (!test_and_set_bit(TCP_WRITE_TIMER_DEFERRED, &sk->sk_tsq_flags))
			sock_hold(sk);
	}
	bh_unlock_sock(sk);
	sock_put(sk);
}