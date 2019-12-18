#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ rcv_tsecr; } ;
struct tcp_sock {scalar_t__ rcv_rtt_last_tsecr; TYPE_2__ rx_opt; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {scalar_t__ end_seq; scalar_t__ seq; } ;
struct TYPE_5__ {scalar_t__ rcv_mss; } ;
struct TYPE_7__ {TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 int INT_MAX ; 
 TYPE_4__* TCP_SKB_CB (struct sk_buff const*) ; 
 int TCP_TS_HZ ; 
 int USEC_PER_SEC ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  tcp_rcv_rtt_update (struct tcp_sock*,int,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_time_stamp (struct tcp_sock*) ; 

__attribute__((used)) static inline void tcp_rcv_rtt_measure_ts(struct sock *sk,
					  const struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tp->rx_opt.rcv_tsecr == tp->rcv_rtt_last_tsecr)
		return;
	tp->rcv_rtt_last_tsecr = tp->rx_opt.rcv_tsecr;

	if (TCP_SKB_CB(skb)->end_seq -
	    TCP_SKB_CB(skb)->seq >= inet_csk(sk)->icsk_ack.rcv_mss) {
		u32 delta = tcp_time_stamp(tp) - tp->rx_opt.rcv_tsecr;
		u32 delta_us;

		if (likely(delta < INT_MAX / (USEC_PER_SEC / TCP_TS_HZ))) {
			if (!delta)
				delta = 1;
			delta_us = delta * (USEC_PER_SEC / TCP_TS_HZ);
			tcp_rcv_rtt_update(tp, delta_us, 0);
		}
	}
}