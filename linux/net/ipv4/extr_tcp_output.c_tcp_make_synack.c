#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct tcphdr {int syn; int ack; int doff; int /*<<< orphan*/  hash_location; void* window; void* ack_seq; void* seq; int /*<<< orphan*/  dest; void* source; } ;
struct tcp_sock {int dummy; } ;
struct tcp_out_options {int syn; int ack; int doff; int /*<<< orphan*/  hash_location; void* window; void* ack_seq; void* seq; int /*<<< orphan*/  dest; void* source; } ;
struct tcp_md5sig_key {int dummy; } ;
struct tcp_fastopen_cookie {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {void* skb_mstamp_ns; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  mark; scalar_t__ data; } ;
struct request_sock {int cookie_ts; int /*<<< orphan*/  rsk_rcv_wnd; } ;
struct inet_request_sock {int /*<<< orphan*/  ir_mark; int /*<<< orphan*/  ir_rmt_port; int /*<<< orphan*/  ir_num; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  enum tcp_synack_type { ____Placeholder_tcp_synack_type } tcp_synack_type ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {TYPE_1__* af_specific; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  snt_isn; int /*<<< orphan*/  txhash; scalar_t__ snt_synack; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* calc_md5_hash ) (int /*<<< orphan*/ ,struct tcp_md5sig_key*,struct sock*,struct sk_buff*) ;struct tcp_md5sig_key* (* req_md5_lookup ) (struct sock const*,struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_TCP_HEADER ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 int /*<<< orphan*/  TCP_MIB_OUTSEGS ; 
#define  TCP_SYNACK_COOKIE 130 
#define  TCP_SYNACK_FASTOPEN 129 
#define  TCP_SYNACK_NORMAL 128 
 int /*<<< orphan*/  __TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cookie_init_timestamp (struct request_sock*) ; 
 int /*<<< orphan*/  dst_metric_advmss (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  memset (struct tcphdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sock* req_to_sk (struct request_sock*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 struct tcp_md5sig_key* stub1 (struct sock const*,struct sock*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct tcp_md5sig_key*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_add_tx_delay (struct sk_buff*,struct tcp_sock const*) ; 
 void* tcp_clock_ns () ; 
 int /*<<< orphan*/  tcp_ecn_make_synack (struct request_sock*,struct tcphdr*) ; 
 int tcp_mss_clamp (struct tcp_sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_options_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tcphdr*) ; 
 TYPE_2__* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 
 scalar_t__ tcp_skb_timestamp_us (struct sk_buff*) ; 
 int tcp_synack_options (struct sock const*,struct request_sock*,int,struct sk_buff*,struct tcphdr*,struct tcp_md5sig_key*,struct tcp_fastopen_cookie*) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *tcp_make_synack(const struct sock *sk, struct dst_entry *dst,
				struct request_sock *req,
				struct tcp_fastopen_cookie *foc,
				enum tcp_synack_type synack_type)
{
	struct inet_request_sock *ireq = inet_rsk(req);
	const struct tcp_sock *tp = tcp_sk(sk);
	struct tcp_md5sig_key *md5 = NULL;
	struct tcp_out_options opts;
	struct sk_buff *skb;
	int tcp_header_size;
	struct tcphdr *th;
	int mss;
	u64 now;

	skb = alloc_skb(MAX_TCP_HEADER, GFP_ATOMIC);
	if (unlikely(!skb)) {
		dst_release(dst);
		return NULL;
	}
	/* Reserve space for headers. */
	skb_reserve(skb, MAX_TCP_HEADER);

	switch (synack_type) {
	case TCP_SYNACK_NORMAL:
		skb_set_owner_w(skb, req_to_sk(req));
		break;
	case TCP_SYNACK_COOKIE:
		/* Under synflood, we do not attach skb to a socket,
		 * to avoid false sharing.
		 */
		break;
	case TCP_SYNACK_FASTOPEN:
		/* sk is a const pointer, because we want to express multiple
		 * cpu might call us concurrently.
		 * sk->sk_wmem_alloc in an atomic, we can promote to rw.
		 */
		skb_set_owner_w(skb, (struct sock *)sk);
		break;
	}
	skb_dst_set(skb, dst);

	mss = tcp_mss_clamp(tp, dst_metric_advmss(dst));

	memset(&opts, 0, sizeof(opts));
	now = tcp_clock_ns();
#ifdef CONFIG_SYN_COOKIES
	if (unlikely(req->cookie_ts))
		skb->skb_mstamp_ns = cookie_init_timestamp(req);
	else
#endif
	{
		skb->skb_mstamp_ns = now;
		if (!tcp_rsk(req)->snt_synack) /* Timestamp first SYNACK */
			tcp_rsk(req)->snt_synack = tcp_skb_timestamp_us(skb);
	}

#ifdef CONFIG_TCP_MD5SIG
	rcu_read_lock();
	md5 = tcp_rsk(req)->af_specific->req_md5_lookup(sk, req_to_sk(req));
#endif
	skb_set_hash(skb, tcp_rsk(req)->txhash, PKT_HASH_TYPE_L4);
	tcp_header_size = tcp_synack_options(sk, req, mss, skb, &opts, md5,
					     foc) + sizeof(*th);

	skb_push(skb, tcp_header_size);
	skb_reset_transport_header(skb);

	th = (struct tcphdr *)skb->data;
	memset(th, 0, sizeof(struct tcphdr));
	th->syn = 1;
	th->ack = 1;
	tcp_ecn_make_synack(req, th);
	th->source = htons(ireq->ir_num);
	th->dest = ireq->ir_rmt_port;
	skb->mark = ireq->ir_mark;
	skb->ip_summed = CHECKSUM_PARTIAL;
	th->seq = htonl(tcp_rsk(req)->snt_isn);
	/* XXX data is queued and acked as is. No buffer/window check */
	th->ack_seq = htonl(tcp_rsk(req)->rcv_nxt);

	/* RFC1323: The window in SYN & SYN/ACK segments is never scaled. */
	th->window = htons(min(req->rsk_rcv_wnd, 65535U));
	tcp_options_write((__be32 *)(th + 1), NULL, &opts);
	th->doff = (tcp_header_size >> 2);
	__TCP_INC_STATS(sock_net(sk), TCP_MIB_OUTSEGS);

#ifdef CONFIG_TCP_MD5SIG
	/* Okay, we have all we need - do the md5 hash if needed */
	if (md5)
		tcp_rsk(req)->af_specific->calc_md5_hash(opts.hash_location,
					       md5, req_to_sk(req), skb);
	rcu_read_unlock();
#endif

	skb->skb_mstamp_ns = now;
	tcp_add_tx_delay(skb, tp);

	return skb;
}