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
struct tcp_sock {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {scalar_t__ icsk_ca_state; scalar_t__ icsk_pending; TYPE_1__* icsk_ca_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  cong_control; } ;

/* Variables and functions */
 scalar_t__ ICSK_TIME_RETRANS ; 
 scalar_t__ TCP_CA_Recovery ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_cwnd_reduction (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_enter_recovery (struct sock*,int) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_rack_detect_loss (struct sock*,scalar_t__*) ; 
 int /*<<< orphan*/  tcp_rearm_rto (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_xmit_retransmit_queue (struct sock*) ; 

void tcp_rack_reo_timeout(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 timeout, prior_inflight;

	prior_inflight = tcp_packets_in_flight(tp);
	tcp_rack_detect_loss(sk, &timeout);
	if (prior_inflight != tcp_packets_in_flight(tp)) {
		if (inet_csk(sk)->icsk_ca_state != TCP_CA_Recovery) {
			tcp_enter_recovery(sk, false);
			if (!inet_csk(sk)->icsk_ca_ops->cong_control)
				tcp_cwnd_reduction(sk, 1, 0);
		}
		tcp_xmit_retransmit_queue(sk);
	}
	if (inet_csk(sk)->icsk_pending != ICSK_TIME_RETRANS)
		tcp_rearm_rto(sk);
}