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
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct TYPE_3__ {TYPE_2__ compressed_ack_timer; TYPE_2__ pacing_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS_PINNED_SOFT ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED_SOFT ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_init_xmit_timers (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_compressed_ack_kick ; 
 int /*<<< orphan*/  tcp_delack_timer ; 
 int /*<<< orphan*/  tcp_keepalive_timer ; 
 int /*<<< orphan*/  tcp_pace_kick ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_timer ; 

void tcp_init_xmit_timers(struct sock *sk)
{
	inet_csk_init_xmit_timers(sk, &tcp_write_timer, &tcp_delack_timer,
				  &tcp_keepalive_timer);
	hrtimer_init(&tcp_sk(sk)->pacing_timer, CLOCK_MONOTONIC,
		     HRTIMER_MODE_ABS_PINNED_SOFT);
	tcp_sk(sk)->pacing_timer.function = tcp_pace_kick;

	hrtimer_init(&tcp_sk(sk)->compressed_ack_timer, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL_PINNED_SOFT);
	tcp_sk(sk)->compressed_ack_timer.function = tcp_compressed_ack_kick;
}