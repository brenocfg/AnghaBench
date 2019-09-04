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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPABORTFAILED ; 
 int /*<<< orphan*/  MAX_TCP_HEADER ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCPHDR_ACK ; 
 int TCPHDR_RST ; 
 int /*<<< orphan*/  TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MIB_OUTRSTS ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_acceptable_seq (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_nondata_skb (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 
 scalar_t__ tcp_transmit_skb (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tcp_send_reset (struct sock*,int /*<<< orphan*/ *) ; 

void tcp_send_active_reset(struct sock *sk, gfp_t priority)
{
	struct sk_buff *skb;

	TCP_INC_STATS(sock_net(sk), TCP_MIB_OUTRSTS);

	/* NOTE: No TCP options attached and we never retransmit this. */
	skb = alloc_skb(MAX_TCP_HEADER, priority);
	if (!skb) {
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTFAILED);
		return;
	}

	/* Reserve space for headers and prepare control bits. */
	skb_reserve(skb, MAX_TCP_HEADER);
	tcp_init_nondata_skb(skb, tcp_acceptable_seq(sk),
			     TCPHDR_ACK | TCPHDR_RST);
	tcp_mstamp_refresh(tcp_sk(sk));
	/* Send it off. */
	if (tcp_transmit_skb(sk, skb, 0, priority))
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTFAILED);

	/* skb of trace_tcp_send_reset() keeps the skb that caused RST,
	 * skb here is different to the troublesome skb, so use NULL
	 */
	trace_tcp_send_reset(sk, NULL);
}