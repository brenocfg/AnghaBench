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
struct tcp_timewait_sock {int tw_rcv_wnd; int /*<<< orphan*/  tw_ts_recent; scalar_t__ tw_ts_offset; int /*<<< orphan*/  tw_rcv_nxt; int /*<<< orphan*/  tw_snd_nxt; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_timewait_sock {int tw_rcv_wscale; int /*<<< orphan*/  tw_priority; int /*<<< orphan*/  tw_flowlabel; int /*<<< orphan*/  tw_tclass; int /*<<< orphan*/  tw_bound_dev_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct inet_timewait_sock* inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 scalar_t__ tcp_time_stamp_raw () ; 
 struct tcp_timewait_sock* tcp_twsk (struct sock*) ; 
 int /*<<< orphan*/  tcp_twsk_md5_key (struct tcp_timewait_sock*) ; 
 int /*<<< orphan*/  tcp_v6_send_ack (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_v6_timewait_ack(struct sock *sk, struct sk_buff *skb)
{
	struct inet_timewait_sock *tw = inet_twsk(sk);
	struct tcp_timewait_sock *tcptw = tcp_twsk(sk);

	tcp_v6_send_ack(sk, skb, tcptw->tw_snd_nxt, tcptw->tw_rcv_nxt,
			tcptw->tw_rcv_wnd >> tw->tw_rcv_wscale,
			tcp_time_stamp_raw() + tcptw->tw_ts_offset,
			tcptw->tw_ts_recent, tw->tw_bound_dev_if, tcp_twsk_md5_key(tcptw),
			tw->tw_tclass, cpu_to_be32(tw->tw_flowlabel), tw->tw_priority);

	inet_twsk_put(tw);
}