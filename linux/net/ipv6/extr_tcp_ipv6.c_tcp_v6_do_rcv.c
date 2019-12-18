#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {scalar_t__ rcv_nxt; } ;
struct sock {int sk_state; struct dst_entry* sk_rx_dst; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ skb_iif; } ;
struct TYPE_11__ {scalar_t__ rxtclass; scalar_t__ rxflow; scalar_t__ rxohlim; scalar_t__ rxhlim; scalar_t__ rxoinfo; scalar_t__ rxinfo; } ;
struct TYPE_12__ {TYPE_2__ bits; scalar_t__ all; } ;
struct ipv6_pinfo {int /*<<< orphan*/  pktoptions; int /*<<< orphan*/  flow_label; scalar_t__ repflow; int /*<<< orphan*/  rcv_flowinfo; TYPE_3__ rxopt; int /*<<< orphan*/  mcast_hops; int /*<<< orphan*/  mcast_oif; int /*<<< orphan*/  rx_dst_cookie; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_13__ {int /*<<< orphan*/  h6; } ;
struct TYPE_16__ {scalar_t__ end_seq; TYPE_4__ header; } ;
struct TYPE_15__ {scalar_t__ rx_dst_ifindex; } ;
struct TYPE_14__ {int /*<<< orphan*/  hop_limit; } ;
struct TYPE_10__ {int /*<<< orphan*/ * (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 int TCP_ESTABLISHED ; 
 int /*<<< orphan*/  TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 TYPE_9__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_8__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_flowinfo (TYPE_5__*) ; 
 int /*<<< orphan*/  ip6_flowlabel (TYPE_5__*) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_opt_accepted (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_gfp_mask (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/ * stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_checksum_complete (struct sk_buff*) ; 
 scalar_t__ tcp_child_process (struct sock*,struct sock*,struct sk_buff*) ; 
 struct ipv6_pinfo* tcp_inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_rcv_established (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_rcv_state_process (struct sock*,struct sk_buff*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_v4_do_rcv (struct sock*,struct sk_buff*) ; 
 struct sock* tcp_v6_cookie_check (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_restore_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_send_reset (struct sock*,struct sk_buff*) ; 
 struct sk_buff* xchg (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int tcp_v6_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct ipv6_pinfo *np = tcp_inet6_sk(sk);
	struct sk_buff *opt_skb = NULL;
	struct tcp_sock *tp;

	/* Imagine: socket is IPv6. IPv4 packet arrives,
	   goes to IPv4 receive handler and backlogged.
	   From backlog it always goes here. Kerboom...
	   Fortunately, tcp_rcv_established and rcv_established
	   handle them correctly, but it is not case with
	   tcp_v6_hnd_req and tcp_v6_send_reset().   --ANK
	 */

	if (skb->protocol == htons(ETH_P_IP))
		return tcp_v4_do_rcv(sk, skb);

	/*
	 *	socket locking is here for SMP purposes as backlog rcv
	 *	is currently called with bh processing disabled.
	 */

	/* Do Stevens' IPV6_PKTOPTIONS.

	   Yes, guys, it is the only place in our code, where we
	   may make it not affecting IPv4.
	   The rest of code is protocol independent,
	   and I do not like idea to uglify IPv4.

	   Actually, all the idea behind IPV6_PKTOPTIONS
	   looks not very well thought. For now we latch
	   options, received in the last packet, enqueued
	   by tcp. Feel free to propose better solution.
					       --ANK (980728)
	 */
	if (np->rxopt.all)
		opt_skb = skb_clone(skb, sk_gfp_mask(sk, GFP_ATOMIC));

	if (sk->sk_state == TCP_ESTABLISHED) { /* Fast path */
		struct dst_entry *dst = sk->sk_rx_dst;

		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		if (dst) {
			if (inet_sk(sk)->rx_dst_ifindex != skb->skb_iif ||
			    dst->ops->check(dst, np->rx_dst_cookie) == NULL) {
				dst_release(dst);
				sk->sk_rx_dst = NULL;
			}
		}

		tcp_rcv_established(sk, skb);
		if (opt_skb)
			goto ipv6_pktoptions;
		return 0;
	}

	if (tcp_checksum_complete(skb))
		goto csum_err;

	if (sk->sk_state == TCP_LISTEN) {
		struct sock *nsk = tcp_v6_cookie_check(sk, skb);

		if (!nsk)
			goto discard;

		if (nsk != sk) {
			if (tcp_child_process(sk, nsk, skb))
				goto reset;
			if (opt_skb)
				__kfree_skb(opt_skb);
			return 0;
		}
	} else
		sock_rps_save_rxhash(sk, skb);

	if (tcp_rcv_state_process(sk, skb))
		goto reset;
	if (opt_skb)
		goto ipv6_pktoptions;
	return 0;

reset:
	tcp_v6_send_reset(sk, skb);
discard:
	if (opt_skb)
		__kfree_skb(opt_skb);
	kfree_skb(skb);
	return 0;
csum_err:
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMERRORS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INERRS);
	goto discard;


ipv6_pktoptions:
	/* Do you ask, what is it?

	   1. skb was enqueued by tcp.
	   2. skb is added to tail of read queue, rather than out of order.
	   3. socket is not in passive state.
	   4. Finally, it really contains options, which user wants to receive.
	 */
	tp = tcp_sk(sk);
	if (TCP_SKB_CB(opt_skb)->end_seq == tp->rcv_nxt &&
	    !((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN))) {
		if (np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo)
			np->mcast_oif = tcp_v6_iif(opt_skb);
		if (np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim)
			np->mcast_hops = ipv6_hdr(opt_skb)->hop_limit;
		if (np->rxopt.bits.rxflow || np->rxopt.bits.rxtclass)
			np->rcv_flowinfo = ip6_flowinfo(ipv6_hdr(opt_skb));
		if (np->repflow)
			np->flow_label = ip6_flowlabel(ipv6_hdr(opt_skb));
		if (ipv6_opt_accepted(sk, opt_skb, &TCP_SKB_CB(opt_skb)->header.h6)) {
			skb_set_owner_r(opt_skb, sk);
			tcp_v6_restore_cb(opt_skb);
			opt_skb = xchg(&np->pktoptions, opt_skb);
		} else {
			__kfree_skb(opt_skb);
			opt_skb = xchg(&np->pktoptions, NULL);
		}
	}

	kfree_skb(opt_skb);
	return 0;
}