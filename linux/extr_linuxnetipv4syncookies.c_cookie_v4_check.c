#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tcp_opt ;
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  seq; scalar_t__ rst; int /*<<< orphan*/  ack; int /*<<< orphan*/  ack_seq; } ;
struct tcp_sock {scalar_t__ window_clamp; } ;
struct tcp_request_sock {int tfo_listener; scalar_t__ snt_synack; int /*<<< orphan*/  txhash; scalar_t__ ts_off; void* snt_isn; void* rcv_isn; } ;
struct tcp_options_received {int /*<<< orphan*/  rcv_tsval; scalar_t__ saw_tstamp; int /*<<< orphan*/  wscale_ok; int /*<<< orphan*/  sack_ok; int /*<<< orphan*/  snd_wscale; scalar_t__ rcv_tsecr; } ;
struct sock {int /*<<< orphan*/  sk_uid; } ;
struct sk_buff {int dummy; } ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct request_sock {int mss; int /*<<< orphan*/  rsk_window_clamp; int /*<<< orphan*/  rsk_rcv_wnd; scalar_t__ num_retrans; int /*<<< orphan*/  ts_recent; } ;
struct ip_options {int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct inet_request_sock {int /*<<< orphan*/  ecn_ok; int /*<<< orphan*/  rcv_wscale; int /*<<< orphan*/  wscale_ok; int /*<<< orphan*/  ir_loc_addr; int /*<<< orphan*/  ir_rmt_addr; int /*<<< orphan*/  ir_mark; int /*<<< orphan*/  ir_iif; int /*<<< orphan*/  ireq_opt; scalar_t__ smc_ok; scalar_t__ tstamp_ok; int /*<<< orphan*/  sack_ok; int /*<<< orphan*/  snd_wscale; int /*<<< orphan*/  ir_rmt_port; int /*<<< orphan*/  ir_num; } ;
struct flowi4 {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  void* __u32 ;
struct TYPE_26__ {int /*<<< orphan*/  sysctl_tcp_syncookies; } ;
struct TYPE_28__ {TYPE_5__ ipv4; } ;
struct TYPE_27__ {struct flowi4 ip4; } ;
struct TYPE_24__ {struct ip_options opt; } ;
struct TYPE_25__ {TYPE_3__ h4; } ;
struct TYPE_22__ {TYPE_6__ u; } ;
struct TYPE_23__ {TYPE_1__ fl; } ;
struct TYPE_21__ {TYPE_4__ header; } ;
struct TYPE_20__ {TYPE_2__ cork; } ;
struct TYPE_19__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SMC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  LINUX_MIB_SYNCOOKIESFAILED ; 
 int /*<<< orphan*/  LINUX_MIB_SYNCOOKIESRECV ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTAX_INITRWND ; 
 int /*<<< orphan*/  RTAX_WINDOW ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock*) ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 TYPE_18__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __NET_INC_STATS (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int __cookie_v4_check (TYPE_12__*,struct tcphdr const*,void*) ; 
 int /*<<< orphan*/  cookie_ecn_ok (struct tcp_options_received*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cookie_timestamp_decode (TYPE_7__*,struct tcp_options_received*) ; 
 int /*<<< orphan*/  dst_metric (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowi4_init_output (struct flowi4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowi4_to_flowi (struct flowi4*) ; 
 struct request_sock* inet_reqsk_alloc (int /*<<< orphan*/ *,struct sock*,int) ; 
 int /*<<< orphan*/  inet_request_bound_dev_if (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  inet_request_mark (struct sock*,struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 TYPE_13__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_sk_flowi_flags (struct sock*) ; 
 TYPE_12__* ip_hdr (struct sk_buff*) ; 
 struct rtable* ip_route_output_key (TYPE_7__*,struct flowi4*) ; 
 int /*<<< orphan*/  memset (struct tcp_options_received*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_tx_rndhash () ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 int /*<<< orphan*/  reqsk_free (struct request_sock*) ; 
 scalar_t__ secure_tcp_ts_off (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ security_inet_conn_request (struct sock*,struct sk_buff*,struct request_sock*) ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_daddr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_rcv_saddr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_full_space (struct sock*) ; 
 struct sock* tcp_get_cookie_sock (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_parse_options (TYPE_7__*,struct sk_buff*,struct tcp_options_received*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_request_sock_ops ; 
 struct tcp_request_sock* tcp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  tcp_select_initial_window (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_synq_no_recent_overflow (struct sock*) ; 
 int /*<<< orphan*/  tcp_v4_save_options (TYPE_7__*,struct sk_buff*) ; 

struct sock *cookie_v4_check(struct sock *sk, struct sk_buff *skb)
{
	struct ip_options *opt = &TCP_SKB_CB(skb)->header.h4.opt;
	struct tcp_options_received tcp_opt;
	struct inet_request_sock *ireq;
	struct tcp_request_sock *treq;
	struct tcp_sock *tp = tcp_sk(sk);
	const struct tcphdr *th = tcp_hdr(skb);
	__u32 cookie = ntohl(th->ack_seq) - 1;
	struct sock *ret = sk;
	struct request_sock *req;
	int mss;
	struct rtable *rt;
	__u8 rcv_wscale;
	struct flowi4 fl4;
	u32 tsoff = 0;

	if (!sock_net(sk)->ipv4.sysctl_tcp_syncookies || !th->ack || th->rst)
		goto out;

	if (tcp_synq_no_recent_overflow(sk))
		goto out;

	mss = __cookie_v4_check(ip_hdr(skb), th, cookie);
	if (mss == 0) {
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESFAILED);
		goto out;
	}

	__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESRECV);

	/* check for timestamp cookie support */
	memset(&tcp_opt, 0, sizeof(tcp_opt));
	tcp_parse_options(sock_net(sk), skb, &tcp_opt, 0, NULL);

	if (tcp_opt.saw_tstamp && tcp_opt.rcv_tsecr) {
		tsoff = secure_tcp_ts_off(sock_net(sk),
					  ip_hdr(skb)->daddr,
					  ip_hdr(skb)->saddr);
		tcp_opt.rcv_tsecr -= tsoff;
	}

	if (!cookie_timestamp_decode(sock_net(sk), &tcp_opt))
		goto out;

	ret = NULL;
	req = inet_reqsk_alloc(&tcp_request_sock_ops, sk, false); /* for safety */
	if (!req)
		goto out;

	ireq = inet_rsk(req);
	treq = tcp_rsk(req);
	treq->rcv_isn		= ntohl(th->seq) - 1;
	treq->snt_isn		= cookie;
	treq->ts_off		= 0;
	treq->txhash		= net_tx_rndhash();
	req->mss		= mss;
	ireq->ir_num		= ntohs(th->dest);
	ireq->ir_rmt_port	= th->source;
	sk_rcv_saddr_set(req_to_sk(req), ip_hdr(skb)->daddr);
	sk_daddr_set(req_to_sk(req), ip_hdr(skb)->saddr);
	ireq->ir_mark		= inet_request_mark(sk, skb);
	ireq->snd_wscale	= tcp_opt.snd_wscale;
	ireq->sack_ok		= tcp_opt.sack_ok;
	ireq->wscale_ok		= tcp_opt.wscale_ok;
	ireq->tstamp_ok		= tcp_opt.saw_tstamp;
	req->ts_recent		= tcp_opt.saw_tstamp ? tcp_opt.rcv_tsval : 0;
	treq->snt_synack	= 0;
	treq->tfo_listener	= false;
	if (IS_ENABLED(CONFIG_SMC))
		ireq->smc_ok = 0;

	ireq->ir_iif = inet_request_bound_dev_if(sk, skb);

	/* We throwed the options of the initial SYN away, so we hope
	 * the ACK carries the same options again (see RFC1122 4.2.3.8)
	 */
	RCU_INIT_POINTER(ireq->ireq_opt, tcp_v4_save_options(sock_net(sk), skb));

	if (security_inet_conn_request(sk, skb, req)) {
		reqsk_free(req);
		goto out;
	}

	req->num_retrans = 0;

	/*
	 * We need to lookup the route here to get at the correct
	 * window size. We should better make sure that the window size
	 * hasn't changed since we received the original syn, but I see
	 * no easy way to do this.
	 */
	flowi4_init_output(&fl4, ireq->ir_iif, ireq->ir_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE, IPPROTO_TCP,
			   inet_sk_flowi_flags(sk),
			   opt->srr ? opt->faddr : ireq->ir_rmt_addr,
			   ireq->ir_loc_addr, th->source, th->dest, sk->sk_uid);
	security_req_classify_flow(req, flowi4_to_flowi(&fl4));
	rt = ip_route_output_key(sock_net(sk), &fl4);
	if (IS_ERR(rt)) {
		reqsk_free(req);
		goto out;
	}

	/* Try to redo what tcp_v4_send_synack did. */
	req->rsk_window_clamp = tp->window_clamp ? :dst_metric(&rt->dst, RTAX_WINDOW);

	tcp_select_initial_window(sk, tcp_full_space(sk), req->mss,
				  &req->rsk_rcv_wnd, &req->rsk_window_clamp,
				  ireq->wscale_ok, &rcv_wscale,
				  dst_metric(&rt->dst, RTAX_INITRWND));

	ireq->rcv_wscale  = rcv_wscale;
	ireq->ecn_ok = cookie_ecn_ok(&tcp_opt, sock_net(sk), &rt->dst);

	ret = tcp_get_cookie_sock(sk, skb, req, &rt->dst, tsoff);
	/* ip_queue_xmit() depends on our flow being setup
	 * Normal sockets get it right from inet_csk_route_child_sock()
	 */
	if (ret)
		inet_sk(ret)->cork.fl.u.ip4 = fl4;
out:	return ret;
}