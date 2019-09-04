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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ compressed_ack; scalar_t__ rcv_nxt; int /*<<< orphan*/  compressed_ack_timer; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICSK_TIME_DACK ; 
 int /*<<< orphan*/  LINUX_MIB_TCPACKCOMPRESSED ; 
 int /*<<< orphan*/  NET_ADD_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TCP_FASTRETRANS_THRESH ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_csk_clear_xmit_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_dec_quickack_mode (struct sock*,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void tcp_event_ack_sent(struct sock *sk, unsigned int pkts,
				      u32 rcv_nxt)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (unlikely(tp->compressed_ack > TCP_FASTRETRANS_THRESH)) {
		NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPACKCOMPRESSED,
			      tp->compressed_ack - TCP_FASTRETRANS_THRESH);
		tp->compressed_ack = TCP_FASTRETRANS_THRESH;
		if (hrtimer_try_to_cancel(&tp->compressed_ack_timer) == 1)
			__sock_put(sk);
	}

	if (unlikely(rcv_nxt != tp->rcv_nxt))
		return;  /* Special ACK sent by DCTCP to reflect ECN */
	tcp_dec_quickack_mode(sk, pkts);
	inet_csk_clear_xmit_timer(sk, ICSK_TIME_DACK);
}