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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int advanced; scalar_t__ end_seq; int /*<<< orphan*/  mstamp; scalar_t__ rtt_us; } ;
struct tcp_sock {TYPE_1__ rack; int /*<<< orphan*/  tcp_mstamp; } ;

/* Variables and functions */
 int TCPCB_RETRANS ; 
 scalar_t__ tcp_min_rtt (struct tcp_sock*) ; 
 scalar_t__ tcp_rack_sent_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ tcp_stamp_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tcp_rack_advance(struct tcp_sock *tp, u8 sacked, u32 end_seq,
		      u64 xmit_time)
{
	u32 rtt_us;

	rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, xmit_time);
	if (rtt_us < tcp_min_rtt(tp) && (sacked & TCPCB_RETRANS)) {
		/* If the sacked packet was retransmitted, it's ambiguous
		 * whether the retransmission or the original (or the prior
		 * retransmission) was sacked.
		 *
		 * If the original is lost, there is no ambiguity. Otherwise
		 * we assume the original can be delayed up to aRTT + min_rtt.
		 * the aRTT term is bounded by the fast recovery or timeout,
		 * so it's at least one RTT (i.e., retransmission is at least
		 * an RTT later).
		 */
		return;
	}
	tp->rack.advanced = 1;
	tp->rack.rtt_us = rtt_us;
	if (tcp_rack_sent_after(xmit_time, tp->rack.mstamp,
				end_seq, tp->rack.end_seq)) {
		tp->rack.mstamp = xmit_time;
		tp->rack.end_seq = end_seq;
	}
}