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
struct sock {scalar_t__ sk_state; } ;
struct TYPE_2__ {struct sock sk; } ;
struct inet_connection_sock {int icsk_pending; scalar_t__ icsk_timeout; int /*<<< orphan*/  icsk_retransmit_timer; TYPE_1__ icsk_inet; } ;

/* Variables and functions */
 scalar_t__ DCCP_CLOSED ; 
 int HZ ; 
#define  ICSK_TIME_RETRANS 128 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  dccp_retransmit_timer (struct sock*) ; 
 struct inet_connection_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* icsk ; 
 int /*<<< orphan*/  icsk_retransmit_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dccp_write_timer(struct timer_list *t)
{
	struct inet_connection_sock *icsk =
			from_timer(icsk, t, icsk_retransmit_timer);
	struct sock *sk = &icsk->icsk_inet.sk;
	int event = 0;

	bh_lock_sock(sk);
	if (sock_owned_by_user(sk)) {
		/* Try again later */
		sk_reset_timer(sk, &icsk->icsk_retransmit_timer,
			       jiffies + (HZ / 20));
		goto out;
	}

	if (sk->sk_state == DCCP_CLOSED || !icsk->icsk_pending)
		goto out;

	if (time_after(icsk->icsk_timeout, jiffies)) {
		sk_reset_timer(sk, &icsk->icsk_retransmit_timer,
			       icsk->icsk_timeout);
		goto out;
	}

	event = icsk->icsk_pending;
	icsk->icsk_pending = 0;

	switch (event) {
	case ICSK_TIME_RETRANS:
		dccp_retransmit_timer(sk);
		break;
	}
out:
	bh_unlock_sock(sk);
	sock_put(sk);
}