#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {scalar_t__ rxtclass; scalar_t__ rxflow; scalar_t__ rxohlim; scalar_t__ rxhlim; scalar_t__ rxoinfo; scalar_t__ rxinfo; } ;
struct TYPE_9__ {TYPE_1__ bits; scalar_t__ all; } ;
struct ipv6_pinfo {int /*<<< orphan*/  pktoptions; int /*<<< orphan*/  flow_label; scalar_t__ repflow; int /*<<< orphan*/  rcv_flowinfo; TYPE_2__ rxopt; int /*<<< orphan*/  mcast_hops; int /*<<< orphan*/  mcast_oif; } ;
struct inet6_skb_parm {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  h6; } ;
struct TYPE_12__ {TYPE_3__ header; } ;
struct TYPE_11__ {int /*<<< orphan*/  hop_limit; } ;

/* Variables and functions */
 int DCCPF_CLOSED ; 
 int DCCPF_LISTEN ; 
 int DCCP_OPEN ; 
 TYPE_7__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_hdr (struct sk_buff*) ; 
 scalar_t__ dccp_rcv_established (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_rcv_state_process (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dccp_v4_do_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_v6_ctl_send_reset (struct sock*,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_flowinfo (TYPE_4__*) ; 
 int /*<<< orphan*/  ip6_flowlabel (TYPE_4__*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_opt_accepted (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sk_filter (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 struct sk_buff* xchg (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int dccp_v6_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *opt_skb = NULL;

	/* Imagine: socket is IPv6. IPv4 packet arrives,
	   goes to IPv4 receive handler and backlogged.
	   From backlog it always goes here. Kerboom...
	   Fortunately, dccp_rcv_established and rcv_established
	   handle them correctly, but it is not case with
	   dccp_v6_hnd_req and dccp_v6_ctl_send_reset().   --ANK
	 */

	if (skb->protocol == htons(ETH_P_IP))
		return dccp_v4_do_rcv(sk, skb);

	if (sk_filter(sk, skb))
		goto discard;

	/*
	 * socket locking is here for SMP purposes as backlog rcv is currently
	 * called with bh processing disabled.
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
		opt_skb = skb_clone(skb, GFP_ATOMIC);

	if (sk->sk_state == DCCP_OPEN) { /* Fast path */
		if (dccp_rcv_established(sk, skb, dccp_hdr(skb), skb->len))
			goto reset;
		if (opt_skb)
			goto ipv6_pktoptions;
		return 0;
	}

	/*
	 *  Step 3: Process LISTEN state
	 *     If S.state == LISTEN,
	 *	 If P.type == Request or P contains a valid Init Cookie option,
	 *	      (* Must scan the packet's options to check for Init
	 *		 Cookies.  Only Init Cookies are processed here,
	 *		 however; other options are processed in Step 8.  This
	 *		 scan need only be performed if the endpoint uses Init
	 *		 Cookies *)
	 *	      (* Generate a new socket and switch to that socket *)
	 *	      Set S := new socket for this port pair
	 *	      S.state = RESPOND
	 *	      Choose S.ISS (initial seqno) or set from Init Cookies
	 *	      Initialize S.GAR := S.ISS
	 *	      Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookies
	 *	      Continue with S.state == RESPOND
	 *	      (* A Response packet will be generated in Step 11 *)
	 *	 Otherwise,
	 *	      Generate Reset(No Connection) unless P.type == Reset
	 *	      Drop packet and return
	 *
	 * NOTE: the check for the packet types is done in
	 *	 dccp_rcv_state_process
	 */

	if (dccp_rcv_state_process(sk, skb, dccp_hdr(skb), skb->len))
		goto reset;
	if (opt_skb)
		goto ipv6_pktoptions;
	return 0;

reset:
	dccp_v6_ctl_send_reset(sk, skb);
discard:
	if (opt_skb != NULL)
		__kfree_skb(opt_skb);
	kfree_skb(skb);
	return 0;

/* Handling IPV6_PKTOPTIONS skb the similar
 * way it's done for net/ipv6/tcp_ipv6.c
 */
ipv6_pktoptions:
	if (!((1 << sk->sk_state) & (DCCPF_CLOSED | DCCPF_LISTEN))) {
		if (np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo)
			np->mcast_oif = inet6_iif(opt_skb);
		if (np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim)
			np->mcast_hops = ipv6_hdr(opt_skb)->hop_limit;
		if (np->rxopt.bits.rxflow || np->rxopt.bits.rxtclass)
			np->rcv_flowinfo = ip6_flowinfo(ipv6_hdr(opt_skb));
		if (np->repflow)
			np->flow_label = ip6_flowlabel(ipv6_hdr(opt_skb));
		if (ipv6_opt_accepted(sk, opt_skb,
				      &DCCP_SKB_CB(opt_skb)->header.h6)) {
			skb_set_owner_r(opt_skb, sk);
			memmove(IP6CB(opt_skb),
				&DCCP_SKB_CB(opt_skb)->header.h6,
				sizeof(struct inet6_skb_parm));
			opt_skb = xchg(&np->pktoptions, opt_skb);
		} else {
			__kfree_skb(opt_skb);
			opt_skb = xchg(&np->pktoptions, NULL);
		}
	}

	kfree_skb(opt_skb);
	return 0;
}