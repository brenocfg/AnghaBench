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
typedef  int u32 ;
struct TYPE_10__ {scalar_t__ num_sacks; scalar_t__ dsack; scalar_t__ saw_tstamp; } ;
struct TYPE_9__ {int reo_wnd_steps; scalar_t__ dsack_seen; scalar_t__ reo_wnd_persist; scalar_t__ last_delivered; scalar_t__ advanced; scalar_t__ mstamp; } ;
struct tcp_sock {scalar_t__ snd_nxt; scalar_t__ write_seq; int copied_seq; int rcv_nxt; int max_window; int snd_cwnd; unsigned int app_limited; scalar_t__ rcv_ooopack; TYPE_5__ rx_opt; scalar_t__ syn_data_acked; TYPE_4__ rack; scalar_t__ last_oow_ack_time; scalar_t__ tlp_high_seq; scalar_t__ sacked_out; scalar_t__ retrans_out; scalar_t__ reord_seen; scalar_t__ dsack_dups; TYPE_3__* duplicate_sack; scalar_t__ bytes_retrans; scalar_t__ bytes_received; scalar_t__ bytes_acked; scalar_t__ bytes_sent; scalar_t__ compressed_ack; scalar_t__ is_sack_reneg; scalar_t__ delivered_ce; scalar_t__ window_clamp; scalar_t__ snd_cwnd_cnt; int /*<<< orphan*/  snd_ssthresh; scalar_t__ rcv_rtt_last_tsecr; int /*<<< orphan*/  mdev_us; scalar_t__ srtt_us; int /*<<< orphan*/  out_of_order_queue; scalar_t__ urg_data; int /*<<< orphan*/  repair; } ;
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/ * page; } ;
struct sock {int sk_state; int sk_userlocks; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;TYPE_1__ sk_frag; int /*<<< orphan*/ * sk_rx_dst; scalar_t__ sk_shutdown; int /*<<< orphan*/ * sk_rx_skb_cache; int /*<<< orphan*/  sk_receive_queue; void* sk_err; } ;
struct inet_sock {scalar_t__ inet_num; scalar_t__ defer_connect; scalar_t__ inet_dport; } ;
struct TYPE_7__ {int /*<<< orphan*/  rcv_mss; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_bind_hash; TYPE_2__ icsk_ack; int /*<<< orphan*/  icsk_rto; scalar_t__ icsk_probes_out; scalar_t__ icsk_backoff; } ;
struct TYPE_8__ {scalar_t__ end_seq; scalar_t__ start_seq; } ;

/* Variables and functions */
 void* ECONNABORTED ; 
 void* ECONNRESET ; 
 int SOCK_BINDADDR_LOCK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int TCPF_CLOSING ; 
 int TCPF_LAST_ACK ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 int TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_INFINITE_SSTHRESH ; 
 int TCP_INIT_CWND ; 
 int TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MIN_MSS ; 
 int TCP_SYN_SENT ; 
 int /*<<< orphan*/  TCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  __kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfp_any () ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_delack_init (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_listen_stop (struct sock*) ; 
 int /*<<< orphan*/  inet_reset_saddr (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_rbtree_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_clear_retrans (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_clear_xmit_timers (struct sock*) ; 
 int /*<<< orphan*/  tcp_fastopen_active_disable_ofo_check (struct sock*) ; 
 int /*<<< orphan*/  tcp_free_fastopen_req (struct tcp_sock*) ; 
 scalar_t__ tcp_need_reset (int) ; 
 int /*<<< orphan*/  tcp_saved_syn_free (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_send_active_reset (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_purge (struct sock*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int tcp_disconnect(struct sock *sk, int flags)
{
	struct inet_sock *inet = inet_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	int old_state = sk->sk_state;
	u32 seq;

	if (old_state != TCP_CLOSE)
		tcp_set_state(sk, TCP_CLOSE);

	/* ABORT function of RFC793 */
	if (old_state == TCP_LISTEN) {
		inet_csk_listen_stop(sk);
	} else if (unlikely(tp->repair)) {
		sk->sk_err = ECONNABORTED;
	} else if (tcp_need_reset(old_state) ||
		   (tp->snd_nxt != tp->write_seq &&
		    (1 << old_state) & (TCPF_CLOSING | TCPF_LAST_ACK))) {
		/* The last check adjusts for discrepancy of Linux wrt. RFC
		 * states
		 */
		tcp_send_active_reset(sk, gfp_any());
		sk->sk_err = ECONNRESET;
	} else if (old_state == TCP_SYN_SENT)
		sk->sk_err = ECONNRESET;

	tcp_clear_xmit_timers(sk);
	__skb_queue_purge(&sk->sk_receive_queue);
	if (sk->sk_rx_skb_cache) {
		__kfree_skb(sk->sk_rx_skb_cache);
		sk->sk_rx_skb_cache = NULL;
	}
	WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);
	tp->urg_data = 0;
	tcp_write_queue_purge(sk);
	tcp_fastopen_active_disable_ofo_check(sk);
	skb_rbtree_purge(&tp->out_of_order_queue);

	inet->inet_dport = 0;

	if (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK))
		inet_reset_saddr(sk);

	sk->sk_shutdown = 0;
	sock_reset_flag(sk, SOCK_DONE);
	tp->srtt_us = 0;
	tp->mdev_us = jiffies_to_usecs(TCP_TIMEOUT_INIT);
	tp->rcv_rtt_last_tsecr = 0;

	seq = tp->write_seq + tp->max_window + 2;
	if (!seq)
		seq = 1;
	WRITE_ONCE(tp->write_seq, seq);

	icsk->icsk_backoff = 0;
	tp->snd_cwnd = 2;
	icsk->icsk_probes_out = 0;
	icsk->icsk_rto = TCP_TIMEOUT_INIT;
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	tp->snd_cwnd = TCP_INIT_CWND;
	tp->snd_cwnd_cnt = 0;
	tp->window_clamp = 0;
	tp->delivered_ce = 0;
	tcp_set_ca_state(sk, TCP_CA_Open);
	tp->is_sack_reneg = 0;
	tcp_clear_retrans(tp);
	inet_csk_delack_init(sk);
	/* Initialize rcv_mss to TCP_MIN_MSS to avoid division by 0
	 * issue in __tcp_select_window()
	 */
	icsk->icsk_ack.rcv_mss = TCP_MIN_MSS;
	memset(&tp->rx_opt, 0, sizeof(tp->rx_opt));
	__sk_dst_reset(sk);
	dst_release(sk->sk_rx_dst);
	sk->sk_rx_dst = NULL;
	tcp_saved_syn_free(tp);
	tp->compressed_ack = 0;
	tp->bytes_sent = 0;
	tp->bytes_acked = 0;
	tp->bytes_received = 0;
	tp->bytes_retrans = 0;
	tp->duplicate_sack[0].start_seq = 0;
	tp->duplicate_sack[0].end_seq = 0;
	tp->dsack_dups = 0;
	tp->reord_seen = 0;
	tp->retrans_out = 0;
	tp->sacked_out = 0;
	tp->tlp_high_seq = 0;
	tp->last_oow_ack_time = 0;
	/* There's a bubble in the pipe until at least the first ACK. */
	tp->app_limited = ~0U;
	tp->rack.mstamp = 0;
	tp->rack.advanced = 0;
	tp->rack.reo_wnd_steps = 1;
	tp->rack.last_delivered = 0;
	tp->rack.reo_wnd_persist = 0;
	tp->rack.dsack_seen = 0;
	tp->syn_data_acked = 0;
	tp->rx_opt.saw_tstamp = 0;
	tp->rx_opt.dsack = 0;
	tp->rx_opt.num_sacks = 0;
	tp->rcv_ooopack = 0;


	/* Clean up fastopen related fields */
	tcp_free_fastopen_req(tp);
	inet->defer_connect = 0;

	WARN_ON(inet->inet_num && !icsk->icsk_bind_hash);

	if (sk->sk_frag.page) {
		put_page(sk->sk_frag.page);
		sk->sk_frag.page = NULL;
		sk->sk_frag.offset = 0;
	}

	sk->sk_error_report(sk);
	return 0;
}