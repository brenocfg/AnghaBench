#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  struct sock {int sk_route_caps; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_v6_rcv_saddr; int /*<<< orphan*/  sk_v6_daddr; int /*<<< orphan*/  sk_backlog_rcv; } const sock ;
struct sk_buff {scalar_t__ protocol; } ;
struct request_sock {int dummy; } ;
struct ipv6_txoptions {scalar_t__ opt_flen; scalar_t__ opt_nflen; } ;
struct TYPE_7__ {int /*<<< orphan*/  all; } ;
struct ipv6_pinfo {int /*<<< orphan*/ * pktoptions; int /*<<< orphan*/ * opt; int /*<<< orphan*/  mcast_hops; int /*<<< orphan*/  mcast_oif; int /*<<< orphan*/ * ipv6_fl_list; int /*<<< orphan*/ * ipv6_ac_list; int /*<<< orphan*/ * ipv6_mc_list; TYPE_2__ rxopt; int /*<<< orphan*/  saddr; } ;
struct inet_sock {void* inet_rcv_saddr; void* inet_saddr; void* inet_daddr; int /*<<< orphan*/ * inet_opt; int /*<<< orphan*/ * pinet6; } ;
struct inet_request_sock {int /*<<< orphan*/ * pktopts; struct ipv6_txoptions* ipv6_opt; int /*<<< orphan*/  ir_iif; int /*<<< orphan*/  ir_v6_loc_addr; int /*<<< orphan*/  ir_v6_rmt_addr; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {TYPE_1__* dev; } ;
struct dccp6_sock {int /*<<< orphan*/  inet6; } ;
struct TYPE_10__ {scalar_t__ icsk_ext_hdr_len; int /*<<< orphan*/  icsk_pmtu_cookie; int /*<<< orphan*/ * icsk_af_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  ttl; } ;
struct TYPE_8__ {int /*<<< orphan*/  hop_limit; } ;
struct TYPE_6__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENDROPS ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 void* LOOPBACK4_IPV6 ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,struct ipv6_txoptions*) ; 
 int /*<<< orphan*/  __NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __inet_inherit_port (struct sock const*,struct sock const*) ; 
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ *) ; 
 struct sock const* dccp_create_openreq_child (struct sock const*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_done (struct sock const*) ; 
 int /*<<< orphan*/  dccp_ipv6_mapped ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_v4_do_rcv ; 
 struct sock const* dccp_v4_request_recv_sock (struct sock const*,struct sk_buff*,struct request_sock*,struct dst_entry*,struct request_sock*,int*) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct dst_entry* inet6_csk_route_req (struct sock const*,struct flowi6*,struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 void* inet6_sk (struct sock const*) ; 
 TYPE_5__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  inet_csk_prepare_forced_close (struct sock const*) ; 
 int inet_ehash_nolisten (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  ip6_dst_store (struct sock const*,struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 struct ipv6_txoptions* ipv6_dup_options (struct sock const*,struct ipv6_txoptions*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct ipv6_pinfo*,struct ipv6_pinfo const*,int) ; 
 struct ipv6_txoptions* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock const*) ; 
 int /*<<< orphan*/ * skb_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (int /*<<< orphan*/ *,struct sock const*) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 

__attribute__((used)) static struct sock *dccp_v6_request_recv_sock(const struct sock *sk,
					      struct sk_buff *skb,
					      struct request_sock *req,
					      struct dst_entry *dst,
					      struct request_sock *req_unhash,
					      bool *own_req)
{
	struct inet_request_sock *ireq = inet_rsk(req);
	struct ipv6_pinfo *newnp;
	const struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6_txoptions *opt;
	struct inet_sock *newinet;
	struct dccp6_sock *newdp6;
	struct sock *newsk;

	if (skb->protocol == htons(ETH_P_IP)) {
		/*
		 *	v6 mapped
		 */
		newsk = dccp_v4_request_recv_sock(sk, skb, req, dst,
						  req_unhash, own_req);
		if (newsk == NULL)
			return NULL;

		newdp6 = (struct dccp6_sock *)newsk;
		newinet = inet_sk(newsk);
		newinet->pinet6 = &newdp6->inet6;
		newnp = inet6_sk(newsk);

		memcpy(newnp, np, sizeof(struct ipv6_pinfo));

		newnp->saddr = newsk->sk_v6_rcv_saddr;

		inet_csk(newsk)->icsk_af_ops = &dccp_ipv6_mapped;
		newsk->sk_backlog_rcv = dccp_v4_do_rcv;
		newnp->pktoptions  = NULL;
		newnp->opt	   = NULL;
		newnp->ipv6_mc_list = NULL;
		newnp->ipv6_ac_list = NULL;
		newnp->ipv6_fl_list = NULL;
		newnp->mcast_oif   = inet_iif(skb);
		newnp->mcast_hops  = ip_hdr(skb)->ttl;

		/*
		 * No need to charge this sock to the relevant IPv6 refcnt debug socks count
		 * here, dccp_create_openreq_child now does this for us, see the comment in
		 * that function for the gory details. -acme
		 */

		/* It is tricky place. Until this moment IPv4 tcp
		   worked with IPv6 icsk.icsk_af_ops.
		   Sync it now.
		 */
		dccp_sync_mss(newsk, inet_csk(newsk)->icsk_pmtu_cookie);

		return newsk;
	}


	if (sk_acceptq_is_full(sk))
		goto out_overflow;

	if (!dst) {
		struct flowi6 fl6;

		dst = inet6_csk_route_req(sk, &fl6, req, IPPROTO_DCCP);
		if (!dst)
			goto out;
	}

	newsk = dccp_create_openreq_child(sk, req, skb);
	if (newsk == NULL)
		goto out_nonewsk;

	/*
	 * No need to charge this sock to the relevant IPv6 refcnt debug socks
	 * count here, dccp_create_openreq_child now does this for us, see the
	 * comment in that function for the gory details. -acme
	 */

	ip6_dst_store(newsk, dst, NULL, NULL);
	newsk->sk_route_caps = dst->dev->features & ~(NETIF_F_IP_CSUM |
						      NETIF_F_TSO);
	newdp6 = (struct dccp6_sock *)newsk;
	newinet = inet_sk(newsk);
	newinet->pinet6 = &newdp6->inet6;
	newnp = inet6_sk(newsk);

	memcpy(newnp, np, sizeof(struct ipv6_pinfo));

	newsk->sk_v6_daddr	= ireq->ir_v6_rmt_addr;
	newnp->saddr		= ireq->ir_v6_loc_addr;
	newsk->sk_v6_rcv_saddr	= ireq->ir_v6_loc_addr;
	newsk->sk_bound_dev_if	= ireq->ir_iif;

	/* Now IPv6 options...

	   First: no IPv4 options.
	 */
	newinet->inet_opt = NULL;

	/* Clone RX bits */
	newnp->rxopt.all = np->rxopt.all;

	newnp->ipv6_mc_list = NULL;
	newnp->ipv6_ac_list = NULL;
	newnp->ipv6_fl_list = NULL;
	newnp->pktoptions = NULL;
	newnp->opt	  = NULL;
	newnp->mcast_oif  = inet6_iif(skb);
	newnp->mcast_hops = ipv6_hdr(skb)->hop_limit;

	/*
	 * Clone native IPv6 options from listening socket (if any)
	 *
	 * Yes, keeping reference count would be much more clever, but we make
	 * one more one thing there: reattach optmem to newsk.
	 */
	opt = ireq->ipv6_opt;
	if (!opt)
		opt = rcu_dereference(np->opt);
	if (opt) {
		opt = ipv6_dup_options(newsk, opt);
		RCU_INIT_POINTER(newnp->opt, opt);
	}
	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	if (opt)
		inet_csk(newsk)->icsk_ext_hdr_len = opt->opt_nflen +
						    opt->opt_flen;

	dccp_sync_mss(newsk, dst_mtu(dst));

	newinet->inet_daddr = newinet->inet_saddr = LOOPBACK4_IPV6;
	newinet->inet_rcv_saddr = LOOPBACK4_IPV6;

	if (__inet_inherit_port(sk, newsk) < 0) {
		inet_csk_prepare_forced_close(newsk);
		dccp_done(newsk);
		goto out;
	}
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash));
	/* Clone pktoptions received with SYN, if we own the req */
	if (*own_req && ireq->pktopts) {
		newnp->pktoptions = skb_clone(ireq->pktopts, GFP_ATOMIC);
		consume_skb(ireq->pktopts);
		ireq->pktopts = NULL;
		if (newnp->pktoptions)
			skb_set_owner_r(newnp->pktoptions, newsk);
	}

	return newsk;

out_overflow:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
out_nonewsk:
	dst_release(dst);
out:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENDROPS);
	return NULL;
}