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
struct tcphdr {int dummy; } ;
struct TYPE_5__ {int reo_wnd_steps; scalar_t__ dsack_seen; scalar_t__ reo_wnd_persist; scalar_t__ last_delivered; scalar_t__ advanced; scalar_t__ mstamp; } ;
struct TYPE_7__ {int snd_wscale; int rcv_wscale; int /*<<< orphan*/  mss_clamp; scalar_t__ ts_recent_stamp; int /*<<< orphan*/  ts_recent; scalar_t__ tstamp_ok; scalar_t__ wscale_ok; int /*<<< orphan*/  sack_ok; scalar_t__ num_sacks; scalar_t__ dsack; scalar_t__ saw_tstamp; } ;
struct tcp_sock {int segs_in; unsigned int app_limited; int snd_wnd; int max_window; int tcp_header_len; TYPE_1__ rack; scalar_t__ syn_data_acked; int /*<<< orphan*/ * fastopen_rsk; int /*<<< orphan*/ * fastopen_req; TYPE_3__ rx_opt; int /*<<< orphan*/  tsoffset; int /*<<< orphan*/  window_clamp; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  rcv_ssthresh; scalar_t__ urg_data; scalar_t__ pushed_seq; scalar_t__ write_seq; scalar_t__ snd_cwnd_cnt; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  total_retrans; scalar_t__ last_oow_ack_time; void* lsndtime; scalar_t__ tlp_high_seq; int /*<<< orphan*/  snd_ssthresh; scalar_t__ sacked_out; scalar_t__ retrans_out; scalar_t__ packets_out; int /*<<< orphan*/  rtt_min; int /*<<< orphan*/  mdev_us; scalar_t__ srtt_us; int /*<<< orphan*/  tsorted_sent_queue; int /*<<< orphan*/  tsq_node; scalar_t__ snd_up; scalar_t__ snd_nxt; scalar_t__ snd_una; scalar_t__ snd_sml; scalar_t__ rcv_nxt; scalar_t__ copied_seq; scalar_t__ rcv_wup; scalar_t__ pred_flags; } ;
struct tcp_request_sock {int /*<<< orphan*/  ts_off; scalar_t__ snt_isn; int /*<<< orphan*/  txhash; scalar_t__ rcv_isn; } ;
typedef  struct sock {int /*<<< orphan*/  sk_txhash; } const sock ;
struct sk_buff {scalar_t__ len; } ;
struct request_sock {int /*<<< orphan*/  mss; int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  rsk_rcv_wnd; int /*<<< orphan*/  rsk_window_clamp; int /*<<< orphan*/  num_retrans; } ;
struct inet_request_sock {int snd_wscale; int rcv_wscale; scalar_t__ wscale_ok; int /*<<< orphan*/  sack_ok; scalar_t__ tstamp_ok; } ;
struct TYPE_6__ {scalar_t__ last_seg_size; void* lrcvtime; } ;
struct inet_connection_sock {TYPE_2__ icsk_ack; int /*<<< orphan*/  icsk_rto; } ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_KEEPOPEN ; 
 int TCPOLEN_TSTAMP_ALIGNED ; 
 int /*<<< orphan*/  TCP_INFINITE_SSTHRESH ; 
 int /*<<< orphan*/  TCP_INIT_CWND ; 
 int /*<<< orphan*/  TCP_MIB_PASSIVEOPENS ; 
 scalar_t__ TCP_MSS_DEFAULT ; 
 int /*<<< orphan*/  TCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  __TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock const*) ; 
 struct sock const* inet_csk_clone_lock (struct sock const*,struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock const*,int /*<<< orphan*/ ) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keepalive_time_when (struct tcp_sock*) ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  minmax_reset (int /*<<< orphan*/ *,void*,unsigned int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_check_reset_syn_req (struct tcp_sock*,struct request_sock*,struct tcp_sock*) ; 
 scalar_t__ sock_flag (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 int /*<<< orphan*/  tcp_ecn_openreq_child (struct tcp_sock*,struct request_sock*) ; 
 TYPE_4__* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_init_wl (struct tcp_sock*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_init_xmit_timers (struct sock const*) ; 
 void* tcp_jiffies32 ; 
 struct tcp_request_sock* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 

struct sock *tcp_create_openreq_child(const struct sock *sk,
				      struct request_sock *req,
				      struct sk_buff *skb)
{
	struct sock *newsk = inet_csk_clone_lock(sk, req, GFP_ATOMIC);
	const struct inet_request_sock *ireq = inet_rsk(req);
	struct tcp_request_sock *treq = tcp_rsk(req);
	struct inet_connection_sock *newicsk;
	struct tcp_sock *oldtp, *newtp;

	if (!newsk)
		return NULL;

	newicsk = inet_csk(newsk);
	newtp = tcp_sk(newsk);
	oldtp = tcp_sk(sk);

	smc_check_reset_syn_req(oldtp, req, newtp);

	/* Now setup tcp_sock */
	newtp->pred_flags = 0;

	newtp->rcv_wup = newtp->copied_seq =
	newtp->rcv_nxt = treq->rcv_isn + 1;
	newtp->segs_in = 1;

	newtp->snd_sml = newtp->snd_una =
	newtp->snd_nxt = newtp->snd_up = treq->snt_isn + 1;

	INIT_LIST_HEAD(&newtp->tsq_node);
	INIT_LIST_HEAD(&newtp->tsorted_sent_queue);

	tcp_init_wl(newtp, treq->rcv_isn);

	newtp->srtt_us = 0;
	newtp->mdev_us = jiffies_to_usecs(TCP_TIMEOUT_INIT);
	minmax_reset(&newtp->rtt_min, tcp_jiffies32, ~0U);
	newicsk->icsk_rto = TCP_TIMEOUT_INIT;
	newicsk->icsk_ack.lrcvtime = tcp_jiffies32;

	newtp->packets_out = 0;
	newtp->retrans_out = 0;
	newtp->sacked_out = 0;
	newtp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	newtp->tlp_high_seq = 0;
	newtp->lsndtime = tcp_jiffies32;
	newsk->sk_txhash = treq->txhash;
	newtp->last_oow_ack_time = 0;
	newtp->total_retrans = req->num_retrans;

	/* So many TCP implementations out there (incorrectly) count the
	 * initial SYN frame in their delayed-ACK and congestion control
	 * algorithms that we must have the following bandaid to talk
	 * efficiently to them.  -DaveM
	 */
	newtp->snd_cwnd = TCP_INIT_CWND;
	newtp->snd_cwnd_cnt = 0;

	/* There's a bubble in the pipe until at least the first ACK. */
	newtp->app_limited = ~0U;

	tcp_init_xmit_timers(newsk);
	newtp->write_seq = newtp->pushed_seq = treq->snt_isn + 1;

	newtp->rx_opt.saw_tstamp = 0;

	newtp->rx_opt.dsack = 0;
	newtp->rx_opt.num_sacks = 0;

	newtp->urg_data = 0;

	if (sock_flag(newsk, SOCK_KEEPOPEN))
		inet_csk_reset_keepalive_timer(newsk,
					       keepalive_time_when(newtp));

	newtp->rx_opt.tstamp_ok = ireq->tstamp_ok;
	newtp->rx_opt.sack_ok = ireq->sack_ok;
	newtp->window_clamp = req->rsk_window_clamp;
	newtp->rcv_ssthresh = req->rsk_rcv_wnd;
	newtp->rcv_wnd = req->rsk_rcv_wnd;
	newtp->rx_opt.wscale_ok = ireq->wscale_ok;
	if (newtp->rx_opt.wscale_ok) {
		newtp->rx_opt.snd_wscale = ireq->snd_wscale;
		newtp->rx_opt.rcv_wscale = ireq->rcv_wscale;
	} else {
		newtp->rx_opt.snd_wscale = newtp->rx_opt.rcv_wscale = 0;
		newtp->window_clamp = min(newtp->window_clamp, 65535U);
	}
	newtp->snd_wnd = ntohs(tcp_hdr(skb)->window) << newtp->rx_opt.snd_wscale;
	newtp->max_window = newtp->snd_wnd;

	if (newtp->rx_opt.tstamp_ok) {
		newtp->rx_opt.ts_recent = req->ts_recent;
		newtp->rx_opt.ts_recent_stamp = ktime_get_seconds();
		newtp->tcp_header_len = sizeof(struct tcphdr) + TCPOLEN_TSTAMP_ALIGNED;
	} else {
		newtp->rx_opt.ts_recent_stamp = 0;
		newtp->tcp_header_len = sizeof(struct tcphdr);
	}
	newtp->tsoffset = treq->ts_off;
#ifdef CONFIG_TCP_MD5SIG
	newtp->md5sig_info = NULL;	/*XXX*/
	if (newtp->af_specific->md5_lookup(sk, newsk))
		newtp->tcp_header_len += TCPOLEN_MD5SIG_ALIGNED;
#endif
	if (skb->len >= TCP_MSS_DEFAULT + newtp->tcp_header_len)
		newicsk->icsk_ack.last_seg_size = skb->len - newtp->tcp_header_len;
	newtp->rx_opt.mss_clamp = req->mss;
	tcp_ecn_openreq_child(newtp, req);
	newtp->fastopen_req = NULL;
	newtp->fastopen_rsk = NULL;
	newtp->syn_data_acked = 0;
	newtp->rack.mstamp = 0;
	newtp->rack.advanced = 0;
	newtp->rack.reo_wnd_steps = 1;
	newtp->rack.last_delivered = 0;
	newtp->rack.reo_wnd_persist = 0;
	newtp->rack.dsack_seen = 0;

	__TCP_INC_STATS(sock_net(sk), TCP_MIB_PASSIVEOPENS);

	return newsk;
}