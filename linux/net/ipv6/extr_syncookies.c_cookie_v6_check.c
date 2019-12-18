#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tcp_opt ;
struct tcphdr {int /*<<< orphan*/  seq; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; scalar_t__ rst; int /*<<< orphan*/  ack; int /*<<< orphan*/  ack_seq; } ;
struct tcp_sock {scalar_t__ window_clamp; } ;
struct tcp_request_sock {int tfo_listener; int /*<<< orphan*/  txhash; scalar_t__ ts_off; void* snt_isn; void* rcv_isn; scalar_t__ snt_synack; } ;
struct TYPE_21__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_17__ {int /*<<< orphan*/  s6_addr32; } ;
struct tcp_options_received {int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  fl6_sport; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowi6_oif; TYPE_2__ saddr; TYPE_10__ daddr; int /*<<< orphan*/  flowi6_proto; int /*<<< orphan*/  rcv_tsval; scalar_t__ saw_tstamp; int /*<<< orphan*/  wscale_ok; int /*<<< orphan*/  sack_ok; int /*<<< orphan*/  snd_wscale; scalar_t__ rcv_tsecr; } ;
struct sock {int /*<<< orphan*/  sk_uid; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;
struct request_sock {int mss; int /*<<< orphan*/  rsk_window_clamp; int /*<<< orphan*/  rsk_rcv_wnd; int /*<<< orphan*/  ts_recent; scalar_t__ num_retrans; } ;
struct TYPE_23__ {scalar_t__ rxohlim; scalar_t__ rxhlim; scalar_t__ rxoinfo; scalar_t__ rxinfo; } ;
struct TYPE_24__ {TYPE_4__ bits; } ;
struct ipv6_pinfo {int /*<<< orphan*/  opt; TYPE_5__ rxopt; } ;
struct inet_request_sock {int /*<<< orphan*/  ecn_ok; int /*<<< orphan*/  rcv_wscale; int /*<<< orphan*/  wscale_ok; int /*<<< orphan*/  ir_rmt_port; int /*<<< orphan*/  ir_mark; int /*<<< orphan*/  ir_iif; TYPE_2__ ir_v6_loc_addr; TYPE_10__ ir_v6_rmt_addr; scalar_t__ smc_ok; scalar_t__ tstamp_ok; int /*<<< orphan*/  sack_ok; int /*<<< orphan*/  snd_wscale; struct sk_buff* pktopts; int /*<<< orphan*/  ir_num; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  fl6_sport; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowi6_oif; TYPE_2__ saddr; TYPE_10__ daddr; int /*<<< orphan*/  flowi6_proto; int /*<<< orphan*/  rcv_tsval; scalar_t__ saw_tstamp; int /*<<< orphan*/  wscale_ok; int /*<<< orphan*/  sack_ok; int /*<<< orphan*/  snd_wscale; scalar_t__ rcv_tsecr; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl6 ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  void* __u32 ;
struct TYPE_26__ {TYPE_2__ daddr; TYPE_10__ saddr; } ;
struct TYPE_20__ {int /*<<< orphan*/  sysctl_tcp_syncookies; } ;
struct TYPE_25__ {TYPE_1__ ipv4; } ;
struct TYPE_22__ {int /*<<< orphan*/  h6; } ;
struct TYPE_19__ {TYPE_3__ header; } ;
struct TYPE_18__ {int /*<<< orphan*/  inet_sport; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SMC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int IPV6_ADDR_LINKLOCAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  LINUX_MIB_SYNCOOKIESFAILED ; 
 int /*<<< orphan*/  LINUX_MIB_SYNCOOKIESRECV ; 
 int /*<<< orphan*/  RTAX_INITRWND ; 
 int /*<<< orphan*/  RTAX_WINDOW ; 
 TYPE_16__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __NET_INC_STATS (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int __cookie_v6_check (TYPE_9__*,struct tcphdr const*,void*) ; 
 int /*<<< orphan*/  cookie_ecn_ok (struct tcp_options_received*,TYPE_6__*,struct dst_entry*) ; 
 int /*<<< orphan*/  cookie_timestamp_decode (TYPE_6__*,struct tcp_options_received*) ; 
 int /*<<< orphan*/  dst_metric (struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct in6_addr* fl6_update_dst (struct tcp_options_received*,int /*<<< orphan*/ ,struct in6_addr*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct tcp_options_received*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct request_sock* inet_reqsk_alloc (int /*<<< orphan*/ *,struct sock*,int) ; 
 int /*<<< orphan*/  inet_request_bound_dev_if (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  inet_request_mark (struct sock*,struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 TYPE_11__* inet_sk (struct sock*) ; 
 struct dst_entry* ip6_dst_lookup_flow (struct sock*,struct tcp_options_received*,struct in6_addr*) ; 
 int ipv6_addr_type (TYPE_10__*) ; 
 TYPE_9__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_opt_accepted (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tcp_options_received*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_tx_rndhash () ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reqsk_free (struct request_sock*) ; 
 scalar_t__ secure_tcpv6_ts_off (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ security_inet_conn_request (struct sock*,struct sk_buff*,struct request_sock*) ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock*,int /*<<< orphan*/ ) ; 
 TYPE_6__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp6_request_sock_ops ; 
 int /*<<< orphan*/  tcp_full_space (struct sock*) ; 
 struct sock* tcp_get_cookie_sock (struct sock*,struct sk_buff*,struct request_sock*,struct dst_entry*,scalar_t__) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_parse_options (TYPE_6__*,struct sk_buff*,struct tcp_options_received*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tcp_request_sock* tcp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  tcp_select_initial_window (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_synq_no_recent_overflow (struct sock*) ; 
 int /*<<< orphan*/  tcp_v6_iif (struct sk_buff*) ; 

struct sock *cookie_v6_check(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_options_received tcp_opt;
	struct inet_request_sock *ireq;
	struct tcp_request_sock *treq;
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	const struct tcphdr *th = tcp_hdr(skb);
	__u32 cookie = ntohl(th->ack_seq) - 1;
	struct sock *ret = sk;
	struct request_sock *req;
	int mss;
	struct dst_entry *dst;
	__u8 rcv_wscale;
	u32 tsoff = 0;

	if (!sock_net(sk)->ipv4.sysctl_tcp_syncookies || !th->ack || th->rst)
		goto out;

	if (tcp_synq_no_recent_overflow(sk))
		goto out;

	mss = __cookie_v6_check(ipv6_hdr(skb), th, cookie);
	if (mss == 0) {
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESFAILED);
		goto out;
	}

	__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESRECV);

	/* check for timestamp cookie support */
	memset(&tcp_opt, 0, sizeof(tcp_opt));
	tcp_parse_options(sock_net(sk), skb, &tcp_opt, 0, NULL);

	if (tcp_opt.saw_tstamp && tcp_opt.rcv_tsecr) {
		tsoff = secure_tcpv6_ts_off(sock_net(sk),
					    ipv6_hdr(skb)->daddr.s6_addr32,
					    ipv6_hdr(skb)->saddr.s6_addr32);
		tcp_opt.rcv_tsecr -= tsoff;
	}

	if (!cookie_timestamp_decode(sock_net(sk), &tcp_opt))
		goto out;

	ret = NULL;
	req = inet_reqsk_alloc(&tcp6_request_sock_ops, sk, false);
	if (!req)
		goto out;

	ireq = inet_rsk(req);
	treq = tcp_rsk(req);
	treq->tfo_listener = false;

	if (security_inet_conn_request(sk, skb, req))
		goto out_free;

	req->mss = mss;
	ireq->ir_rmt_port = th->source;
	ireq->ir_num = ntohs(th->dest);
	ireq->ir_v6_rmt_addr = ipv6_hdr(skb)->saddr;
	ireq->ir_v6_loc_addr = ipv6_hdr(skb)->daddr;
	if (ipv6_opt_accepted(sk, skb, &TCP_SKB_CB(skb)->header.h6) ||
	    np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo ||
	    np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim) {
		refcount_inc(&skb->users);
		ireq->pktopts = skb;
	}

	ireq->ir_iif = inet_request_bound_dev_if(sk, skb);
	/* So that link locals have meaning */
	if (!sk->sk_bound_dev_if &&
	    ipv6_addr_type(&ireq->ir_v6_rmt_addr) & IPV6_ADDR_LINKLOCAL)
		ireq->ir_iif = tcp_v6_iif(skb);

	ireq->ir_mark = inet_request_mark(sk, skb);

	req->num_retrans = 0;
	ireq->snd_wscale	= tcp_opt.snd_wscale;
	ireq->sack_ok		= tcp_opt.sack_ok;
	ireq->wscale_ok		= tcp_opt.wscale_ok;
	ireq->tstamp_ok		= tcp_opt.saw_tstamp;
	req->ts_recent		= tcp_opt.saw_tstamp ? tcp_opt.rcv_tsval : 0;
	treq->snt_synack	= 0;
	treq->rcv_isn = ntohl(th->seq) - 1;
	treq->snt_isn = cookie;
	treq->ts_off = 0;
	treq->txhash = net_tx_rndhash();
	if (IS_ENABLED(CONFIG_SMC))
		ireq->smc_ok = 0;

	/*
	 * We need to lookup the dst_entry to get the correct window size.
	 * This is taken from tcp_v6_syn_recv_sock.  Somebody please enlighten
	 * me if there is a preferred way.
	 */
	{
		struct in6_addr *final_p, final;
		struct flowi6 fl6;
		memset(&fl6, 0, sizeof(fl6));
		fl6.flowi6_proto = IPPROTO_TCP;
		fl6.daddr = ireq->ir_v6_rmt_addr;
		final_p = fl6_update_dst(&fl6, rcu_dereference(np->opt), &final);
		fl6.saddr = ireq->ir_v6_loc_addr;
		fl6.flowi6_oif = ireq->ir_iif;
		fl6.flowi6_mark = ireq->ir_mark;
		fl6.fl6_dport = ireq->ir_rmt_port;
		fl6.fl6_sport = inet_sk(sk)->inet_sport;
		fl6.flowi6_uid = sk->sk_uid;
		security_req_classify_flow(req, flowi6_to_flowi(&fl6));

		dst = ip6_dst_lookup_flow(sk, &fl6, final_p);
		if (IS_ERR(dst))
			goto out_free;
	}

	req->rsk_window_clamp = tp->window_clamp ? :dst_metric(dst, RTAX_WINDOW);
	tcp_select_initial_window(sk, tcp_full_space(sk), req->mss,
				  &req->rsk_rcv_wnd, &req->rsk_window_clamp,
				  ireq->wscale_ok, &rcv_wscale,
				  dst_metric(dst, RTAX_INITRWND));

	ireq->rcv_wscale = rcv_wscale;
	ireq->ecn_ok = cookie_ecn_ok(&tcp_opt, sock_net(sk), dst);

	ret = tcp_get_cookie_sock(sk, skb, req, dst, tsoff);
out:
	return ret;
out_free:
	reqsk_free(req);
	return NULL;
}