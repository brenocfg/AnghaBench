#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ advanced; } ;
struct tcp_sock {TYPE_1__ rack; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_rto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICSK_TIME_REO_TIMEOUT ; 
 scalar_t__ TCP_TIMEOUT_MIN ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_rack_detect_loss (struct sock*,scalar_t__*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ usecs_to_jiffies (scalar_t__) ; 

void tcp_rack_mark_lost(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 timeout;

	if (!tp->rack.advanced)
		return;

	/* Reset the advanced flag to avoid unnecessary queue scanning */
	tp->rack.advanced = 0;
	tcp_rack_detect_loss(sk, &timeout);
	if (timeout) {
		timeout = usecs_to_jiffies(timeout) + TCP_TIMEOUT_MIN;
		inet_csk_reset_xmit_timer(sk, ICSK_TIME_REO_TIMEOUT,
					  timeout, inet_csk(sk)->icsk_rto);
	}
}