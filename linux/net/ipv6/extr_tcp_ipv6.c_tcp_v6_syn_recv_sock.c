#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union tcp_md5_addr {int dummy; } tcp_md5_addr ;
struct tcp_sock {int /*<<< orphan*/  advmss; int /*<<< orphan*/ * af_specific; } ;
struct tcp_md5sig_key {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
typedef  struct sock {int /*<<< orphan*/  sk_v6_daddr; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_v6_rcv_saddr; int /*<<< orphan*/  sk_gso_type; int /*<<< orphan*/  sk_backlog_rcv; } const sock ;
struct sk_buff {scalar_t__ protocol; } ;
struct request_sock {int dummy; } ;
struct ipv6_txoptions {scalar_t__ opt_flen; scalar_t__ opt_nflen; } ;
struct TYPE_7__ {int /*<<< orphan*/  all; } ;
struct ipv6_pinfo {int /*<<< orphan*/ * pktoptions; int /*<<< orphan*/ * opt; scalar_t__ flow_label; scalar_t__ repflow; scalar_t__ rcv_flowinfo; int /*<<< orphan*/  mcast_hops; int /*<<< orphan*/  mcast_oif; TYPE_1__ rxopt; int /*<<< orphan*/ * ipv6_fl_list; int /*<<< orphan*/ * ipv6_ac_list; int /*<<< orphan*/ * ipv6_mc_list; int /*<<< orphan*/  saddr; } ;
struct inet_sock {void* inet_rcv_saddr; void* inet_saddr; void* inet_daddr; int /*<<< orphan*/ * inet_opt; void* pinet6; } ;
struct inet_request_sock {int /*<<< orphan*/ * pktopts; struct ipv6_txoptions* ipv6_opt; int /*<<< orphan*/  ir_iif; int /*<<< orphan*/  ir_v6_loc_addr; int /*<<< orphan*/  ir_v6_rmt_addr; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_10__ {scalar_t__ icsk_ext_hdr_len; int /*<<< orphan*/  icsk_pmtu_cookie; int /*<<< orphan*/ * icsk_af_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  ttl; } ;
struct TYPE_8__ {int /*<<< orphan*/  hop_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 void* LOOPBACK4_IPV6 ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,struct ipv6_txoptions*) ; 
 int /*<<< orphan*/  SKB_GSO_TCPV6 ; 
 int /*<<< orphan*/  __NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __inet_inherit_port (struct sock const*,struct sock const*) ; 
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_metric_advmss (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct dst_entry* inet6_csk_route_req (struct sock const*,struct flowi6*,struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_sk_rx_dst_set (struct sock const*,struct sk_buff*) ; 
 TYPE_6__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  inet_csk_prepare_forced_close (struct sock const*) ; 
 int inet_ehash_nolisten (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  ip6_dst_store (struct sock const*,struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ip6_flowinfo (TYPE_2__*) ; 
 scalar_t__ ip6_flowlabel (TYPE_2__*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 struct ipv6_txoptions* ipv6_dup_options (struct sock const*,struct ipv6_txoptions*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_mapped ; 
 int /*<<< orphan*/  memcpy (struct ipv6_pinfo*,struct ipv6_pinfo const*,int) ; 
 struct ipv6_txoptions* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock const*) ; 
 int /*<<< orphan*/  sk_gfp_mask (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_r (int /*<<< orphan*/ *,struct sock const*) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 int /*<<< orphan*/  tcp_ca_openreq_child (struct sock const*,struct dst_entry*) ; 
 struct sock const* tcp_create_openreq_child (struct sock const*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_done (struct sock const*) ; 
 void* tcp_inet6_sk (struct sock const*) ; 
 int /*<<< orphan*/  tcp_initialize_rcv_mss (struct sock const*) ; 
 int /*<<< orphan*/  tcp_listendrop (struct sock const*) ; 
 int /*<<< orphan*/  tcp_md5_do_add (struct sock const*,union tcp_md5_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_move_syn (struct tcp_sock*,struct request_sock*) ; 
 int /*<<< orphan*/  tcp_mss_clamp (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 
 int /*<<< orphan*/  tcp_sock_ipv6_mapped_specific ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_v4_do_rcv ; 
 struct sock const* tcp_v4_syn_recv_sock (struct sock const*,struct sk_buff*,struct request_sock*,struct dst_entry*,struct request_sock*,int*) ; 
 int /*<<< orphan*/  tcp_v6_iif (struct sk_buff*) ; 
 struct tcp_md5sig_key* tcp_v6_md5_do_lookup (struct sock const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_v6_restore_cb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sock *tcp_v6_syn_recv_sock(const struct sock *sk, struct sk_buff *skb,
					 struct request_sock *req,
					 struct dst_entry *dst,
					 struct request_sock *req_unhash,
					 bool *own_req)
{
	struct inet_request_sock *ireq;
	struct ipv6_pinfo *newnp;
	const struct ipv6_pinfo *np = tcp_inet6_sk(sk);
	struct ipv6_txoptions *opt;
	struct inet_sock *newinet;
	struct tcp_sock *newtp;
	struct sock *newsk;
#ifdef CONFIG_TCP_MD5SIG
	struct tcp_md5sig_key *key;
#endif
	struct flowi6 fl6;

	if (skb->protocol == htons(ETH_P_IP)) {
		/*
		 *	v6 mapped
		 */

		newsk = tcp_v4_syn_recv_sock(sk, skb, req, dst,
					     req_unhash, own_req);

		if (!newsk)
			return NULL;

		inet_sk(newsk)->pinet6 = tcp_inet6_sk(newsk);

		newinet = inet_sk(newsk);
		newnp = tcp_inet6_sk(newsk);
		newtp = tcp_sk(newsk);

		memcpy(newnp, np, sizeof(struct ipv6_pinfo));

		newnp->saddr = newsk->sk_v6_rcv_saddr;

		inet_csk(newsk)->icsk_af_ops = &ipv6_mapped;
		newsk->sk_backlog_rcv = tcp_v4_do_rcv;
#ifdef CONFIG_TCP_MD5SIG
		newtp->af_specific = &tcp_sock_ipv6_mapped_specific;
#endif

		newnp->ipv6_mc_list = NULL;
		newnp->ipv6_ac_list = NULL;
		newnp->ipv6_fl_list = NULL;
		newnp->pktoptions  = NULL;
		newnp->opt	   = NULL;
		newnp->mcast_oif   = inet_iif(skb);
		newnp->mcast_hops  = ip_hdr(skb)->ttl;
		newnp->rcv_flowinfo = 0;
		if (np->repflow)
			newnp->flow_label = 0;

		/*
		 * No need to charge this sock to the relevant IPv6 refcnt debug socks count
		 * here, tcp_create_openreq_child now does this for us, see the comment in
		 * that function for the gory details. -acme
		 */

		/* It is tricky place. Until this moment IPv4 tcp
		   worked with IPv6 icsk.icsk_af_ops.
		   Sync it now.
		 */
		tcp_sync_mss(newsk, inet_csk(newsk)->icsk_pmtu_cookie);

		return newsk;
	}

	ireq = inet_rsk(req);

	if (sk_acceptq_is_full(sk))
		goto out_overflow;

	if (!dst) {
		dst = inet6_csk_route_req(sk, &fl6, req, IPPROTO_TCP);
		if (!dst)
			goto out;
	}

	newsk = tcp_create_openreq_child(sk, req, skb);
	if (!newsk)
		goto out_nonewsk;

	/*
	 * No need to charge this sock to the relevant IPv6 refcnt debug socks
	 * count here, tcp_create_openreq_child now does this for us, see the
	 * comment in that function for the gory details. -acme
	 */

	newsk->sk_gso_type = SKB_GSO_TCPV6;
	ip6_dst_store(newsk, dst, NULL, NULL);
	inet6_sk_rx_dst_set(newsk, skb);

	inet_sk(newsk)->pinet6 = tcp_inet6_sk(newsk);

	newtp = tcp_sk(newsk);
	newinet = inet_sk(newsk);
	newnp = tcp_inet6_sk(newsk);

	memcpy(newnp, np, sizeof(struct ipv6_pinfo));

	newsk->sk_v6_daddr = ireq->ir_v6_rmt_addr;
	newnp->saddr = ireq->ir_v6_loc_addr;
	newsk->sk_v6_rcv_saddr = ireq->ir_v6_loc_addr;
	newsk->sk_bound_dev_if = ireq->ir_iif;

	/* Now IPv6 options...

	   First: no IPv4 options.
	 */
	newinet->inet_opt = NULL;
	newnp->ipv6_mc_list = NULL;
	newnp->ipv6_ac_list = NULL;
	newnp->ipv6_fl_list = NULL;

	/* Clone RX bits */
	newnp->rxopt.all = np->rxopt.all;

	newnp->pktoptions = NULL;
	newnp->opt	  = NULL;
	newnp->mcast_oif  = tcp_v6_iif(skb);
	newnp->mcast_hops = ipv6_hdr(skb)->hop_limit;
	newnp->rcv_flowinfo = ip6_flowinfo(ipv6_hdr(skb));
	if (np->repflow)
		newnp->flow_label = ip6_flowlabel(ipv6_hdr(skb));

	/* Clone native IPv6 options from listening socket (if any)

	   Yes, keeping reference count would be much more clever,
	   but we make one more one thing there: reattach optmem
	   to newsk.
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

	tcp_ca_openreq_child(newsk, dst);

	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = tcp_mss_clamp(tcp_sk(sk), dst_metric_advmss(dst));

	tcp_initialize_rcv_mss(newsk);

	newinet->inet_daddr = newinet->inet_saddr = LOOPBACK4_IPV6;
	newinet->inet_rcv_saddr = LOOPBACK4_IPV6;

#ifdef CONFIG_TCP_MD5SIG
	/* Copy over the MD5 key from the original socket */
	key = tcp_v6_md5_do_lookup(sk, &newsk->sk_v6_daddr);
	if (key) {
		/* We're using one, so create a matching key
		 * on the newsk structure. If we fail to get
		 * memory, then we end up not copying the key
		 * across. Shucks.
		 */
		tcp_md5_do_add(newsk, (union tcp_md5_addr *)&newsk->sk_v6_daddr,
			       AF_INET6, 128, key->key, key->keylen,
			       sk_gfp_mask(sk, GFP_ATOMIC));
	}
#endif

	if (__inet_inherit_port(sk, newsk) < 0) {
		inet_csk_prepare_forced_close(newsk);
		tcp_done(newsk);
		goto out;
	}
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash));
	if (*own_req) {
		tcp_move_syn(newtp, req);

		/* Clone pktoptions received with SYN, if we own the req */
		if (ireq->pktopts) {
			newnp->pktoptions = skb_clone(ireq->pktopts,
						      sk_gfp_mask(sk, GFP_ATOMIC));
			consume_skb(ireq->pktopts);
			ireq->pktopts = NULL;
			if (newnp->pktoptions) {
				tcp_v6_restore_cb(newnp->pktoptions);
				skb_set_owner_r(newnp->pktoptions, newsk);
			}
		}
	}

	return newsk;

out_overflow:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
out_nonewsk:
	dst_release(dst);
out:
	tcp_listendrop(sk);
	return NULL;
}