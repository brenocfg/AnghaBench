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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int rsk_rcv_wnd; int /*<<< orphan*/  ts_recent; } ;
struct TYPE_8__ {int rcv_wscale; } ;
struct TYPE_7__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {scalar_t__ ts_off; int /*<<< orphan*/  rcv_nxt; scalar_t__ snt_isn; } ;
struct TYPE_5__ {scalar_t__ snd_nxt; } ;

/* Variables and functions */
 scalar_t__ TCP_LISTEN ; 
 TYPE_4__* inet_rsk (struct request_sock*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 TYPE_2__* tcp_rsk (struct request_sock*) ; 
 TYPE_1__* tcp_sk (struct sock const*) ; 
 scalar_t__ tcp_time_stamp_raw () ; 
 int /*<<< orphan*/  tcp_v6_md5_do_lookup (struct sock const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_v6_send_ack (struct sock const*,struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_v6_reqsk_send_ack(const struct sock *sk, struct sk_buff *skb,
				  struct request_sock *req)
{
	/* sk->sk_state == TCP_LISTEN -> for regular TCP_SYN_RECV
	 * sk->sk_state == TCP_SYN_RECV -> for Fast Open.
	 */
	/* RFC 7323 2.3
	 * The window field (SEG.WND) of every outgoing segment, with the
	 * exception of <SYN> segments, MUST be right-shifted by
	 * Rcv.Wind.Shift bits:
	 */
	tcp_v6_send_ack(sk, skb, (sk->sk_state == TCP_LISTEN) ?
			tcp_rsk(req)->snt_isn + 1 : tcp_sk(sk)->snd_nxt,
			tcp_rsk(req)->rcv_nxt,
			req->rsk_rcv_wnd >> inet_rsk(req)->rcv_wscale,
			tcp_time_stamp_raw() + tcp_rsk(req)->ts_off,
			req->ts_recent, sk->sk_bound_dev_if,
			tcp_v6_md5_do_lookup(sk, &ipv6_hdr(skb)->saddr),
			0, 0, sk->sk_priority);
}