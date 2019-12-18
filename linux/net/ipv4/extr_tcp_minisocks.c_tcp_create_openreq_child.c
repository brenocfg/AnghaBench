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
typedef  void* u32 ;
struct tcphdr {int dummy; } ;
struct TYPE_7__ {int snd_wscale; int rcv_wscale; int /*<<< orphan*/  mss_clamp; scalar_t__ ts_recent_stamp; int /*<<< orphan*/  ts_recent; scalar_t__ tstamp_ok; scalar_t__ wscale_ok; int /*<<< orphan*/  sack_ok; } ;
struct tcp_sock {int segs_in; void* pushed_seq; int snd_wnd; int max_window; int tcp_header_len; int /*<<< orphan*/  fastopen_rsk; int /*<<< orphan*/ * fastopen_req; TYPE_3__ rx_opt; TYPE_1__* af_specific; int /*<<< orphan*/ * md5sig_info; int /*<<< orphan*/  tsoffset; int /*<<< orphan*/  retrans_stamp; void* undo_marker; int /*<<< orphan*/  window_clamp; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  rcv_ssthresh; int /*<<< orphan*/  write_seq; int /*<<< orphan*/  total_retrans; void* lsndtime; int /*<<< orphan*/  rtt_min; int /*<<< orphan*/  tsorted_sent_queue; int /*<<< orphan*/  tsq_node; void* snd_up; int /*<<< orphan*/  snd_nxt; void* snd_una; void* snd_sml; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  copied_seq; void* rcv_wup; scalar_t__ pred_flags; } ;
struct tcp_request_sock {int /*<<< orphan*/  ts_off; int /*<<< orphan*/  snt_synack; void* snt_isn; int /*<<< orphan*/  txhash; void* rcv_isn; } ;
typedef  struct sock {int /*<<< orphan*/  sk_txhash; } const sock ;
struct sk_buff {scalar_t__ len; } ;
struct request_sock {int /*<<< orphan*/  mss; scalar_t__ num_timeout; int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  rsk_rcv_wnd; int /*<<< orphan*/  rsk_window_clamp; int /*<<< orphan*/  num_retrans; } ;
struct inet_request_sock {int snd_wscale; int rcv_wscale; scalar_t__ wscale_ok; int /*<<< orphan*/  sack_ok; scalar_t__ tstamp_ok; } ;
struct TYPE_6__ {scalar_t__ last_seg_size; void* lrcvtime; } ;
struct inet_connection_sock {TYPE_2__ icsk_ack; } ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
struct TYPE_5__ {scalar_t__ (* md5_lookup ) (struct sock const*,struct sock const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_KEEPOPEN ; 
 scalar_t__ TCPOLEN_MD5SIG_ALIGNED ; 
 int TCPOLEN_TSTAMP_ALIGNED ; 
 int /*<<< orphan*/  TCP_MIB_PASSIVEOPENS ; 
 scalar_t__ TCP_MSS_DEFAULT ; 
 int TCP_TS_HZ ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  __TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int) ; 
 struct inet_connection_sock* inet_csk (struct sock const*) ; 
 struct sock const* inet_csk_clone_lock (struct sock const*,struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock const*,int /*<<< orphan*/ ) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  keepalive_time_when (struct tcp_sock*) ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  minmax_reset (int /*<<< orphan*/ *,void*,unsigned int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_check_reset_syn_req (struct tcp_sock*,struct request_sock*,struct tcp_sock*) ; 
 scalar_t__ sock_flag (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 scalar_t__ stub1 (struct sock const*,struct sock const*) ; 
 int /*<<< orphan*/  tcp_ecn_openreq_child (struct tcp_sock*,struct request_sock*) ; 
 TYPE_4__* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_init_wl (struct tcp_sock*,void*) ; 
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
	u32 seq;

	if (!newsk)
		return NULL;

	newicsk = inet_csk(newsk);
	newtp = tcp_sk(newsk);
	oldtp = tcp_sk(sk);

	smc_check_reset_syn_req(oldtp, req, newtp);

	/* Now setup tcp_sock */
	newtp->pred_flags = 0;

	seq = treq->rcv_isn + 1;
	newtp->rcv_wup = seq;
	WRITE_ONCE(newtp->copied_seq, seq);
	WRITE_ONCE(newtp->rcv_nxt, seq);
	newtp->segs_in = 1;

	seq = treq->snt_isn + 1;
	newtp->snd_sml = newtp->snd_una = seq;
	WRITE_ONCE(newtp->snd_nxt, seq);
	newtp->snd_up = seq;

	INIT_LIST_HEAD(&newtp->tsq_node);
	INIT_LIST_HEAD(&newtp->tsorted_sent_queue);

	tcp_init_wl(newtp, treq->rcv_isn);

	minmax_reset(&newtp->rtt_min, tcp_jiffies32, ~0U);
	newicsk->icsk_ack.lrcvtime = tcp_jiffies32;

	newtp->lsndtime = tcp_jiffies32;
	newsk->sk_txhash = treq->txhash;
	newtp->total_retrans = req->num_retrans;

	tcp_init_xmit_timers(newsk);
	WRITE_ONCE(newtp->write_seq, newtp->pushed_seq = treq->snt_isn + 1);

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
	if (req->num_timeout) {
		newtp->undo_marker = treq->snt_isn;
		newtp->retrans_stamp = div_u64(treq->snt_synack,
					       USEC_PER_SEC / TCP_TS_HZ);
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
	RCU_INIT_POINTER(newtp->fastopen_rsk, NULL);

	__TCP_INC_STATS(sock_net(sk), TCP_MIB_PASSIVEOPENS);

	return newsk;
}