#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {scalar_t__ pushed_seq; int /*<<< orphan*/  snd_nxt; scalar_t__ write_seq; scalar_t__ fastopen_req; int /*<<< orphan*/  retrans_stamp; struct sk_buff* repair; } ;
struct sock {int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  tcp_rtx_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ seq; } ;
struct TYPE_5__ {int /*<<< orphan*/  icsk_rto; TYPE_1__* icsk_af_ops; } ;
struct TYPE_4__ {scalar_t__ (* rebuild_header ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCK_OPS_TCP_CONNECT_CB ; 
 int ECONNREFUSED ; 
 int EHOSTUNREACH ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  TCPHDR_SYN ; 
 int /*<<< orphan*/  TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MIB_ACTIVEOPENS ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* sk_stream_alloc_skb (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_call_bpf (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_connect_init (struct sock*) ; 
 int /*<<< orphan*/  tcp_connect_queue_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_ecn_send_syn (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_finish_connect (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_init_nondata_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_rbtree_insert (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* tcp_send_head (struct sock*) ; 
 int tcp_send_syn_data (struct sock*,struct sk_buff*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp (struct tcp_sock*) ; 
 int tcp_transmit_skb (struct sock*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int tcp_connect(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *buff;
	int err;

	tcp_call_bpf(sk, BPF_SOCK_OPS_TCP_CONNECT_CB, 0, NULL);

	if (inet_csk(sk)->icsk_af_ops->rebuild_header(sk))
		return -EHOSTUNREACH; /* Routing failure or similar. */

	tcp_connect_init(sk);

	if (unlikely(tp->repair)) {
		tcp_finish_connect(sk, NULL);
		return 0;
	}

	buff = sk_stream_alloc_skb(sk, 0, sk->sk_allocation, true);
	if (unlikely(!buff))
		return -ENOBUFS;

	tcp_init_nondata_skb(buff, tp->write_seq++, TCPHDR_SYN);
	tcp_mstamp_refresh(tp);
	tp->retrans_stamp = tcp_time_stamp(tp);
	tcp_connect_queue_skb(sk, buff);
	tcp_ecn_send_syn(sk, buff);
	tcp_rbtree_insert(&sk->tcp_rtx_queue, buff);

	/* Send off SYN; include data in Fast Open. */
	err = tp->fastopen_req ? tcp_send_syn_data(sk, buff) :
	      tcp_transmit_skb(sk, buff, 1, sk->sk_allocation);
	if (err == -ECONNREFUSED)
		return err;

	/* We change tp->snd_nxt after the tcp_transmit_skb() call
	 * in order to make this packet get counted in tcpOutSegs.
	 */
	WRITE_ONCE(tp->snd_nxt, tp->write_seq);
	tp->pushed_seq = tp->write_seq;
	buff = tcp_send_head(sk);
	if (unlikely(buff)) {
		WRITE_ONCE(tp->snd_nxt, TCP_SKB_CB(buff)->seq);
		tp->pushed_seq	= TCP_SKB_CB(buff)->seq;
	}
	TCP_INC_STATS(sock_net(sk), TCP_MIB_ACTIVEOPENS);

	/* Timer for repeating the SYN until an answer. */
	inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
				  inet_csk(sk)->icsk_rto, TCP_RTO_MAX);
	return 0;
}