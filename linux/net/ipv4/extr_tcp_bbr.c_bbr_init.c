#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcp_sock {int /*<<< orphan*/  tcp_mstamp; int /*<<< orphan*/  snd_ssthresh; } ;
struct sock {int /*<<< orphan*/  sk_pacing_status; } ;
struct bbr {scalar_t__* extra_acked; scalar_t__ extra_acked_win_idx; scalar_t__ extra_acked_win_rtts; scalar_t__ ack_epoch_acked; int /*<<< orphan*/  ack_epoch_mstamp; scalar_t__ cycle_idx; scalar_t__ cycle_mstamp; scalar_t__ full_bw_cnt; scalar_t__ full_bw; scalar_t__ full_bw_reached; scalar_t__ idle_restart; scalar_t__ round_start; scalar_t__ has_seen_rtt; scalar_t__ rtt_cnt; int /*<<< orphan*/  bw; int /*<<< orphan*/  min_rtt_stamp; int /*<<< orphan*/  min_rtt_us; scalar_t__ probe_rtt_round_done; scalar_t__ probe_rtt_done_stamp; scalar_t__ packet_conservation; int /*<<< orphan*/  prev_ca_state; scalar_t__ next_rtt_delivered; scalar_t__ prior_cwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_PACING_NEEDED ; 
 int /*<<< orphan*/  SK_PACING_NONE ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 int /*<<< orphan*/  TCP_INFINITE_SSTHRESH ; 
 int /*<<< orphan*/  bbr_init_pacing_rate_from_rtt (struct sock*) ; 
 int /*<<< orphan*/  bbr_reset_lt_bw_sampling (struct sock*) ; 
 int /*<<< orphan*/  bbr_reset_startup_mode (struct sock*) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  minmax_reset (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_min_rtt (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bbr_init(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bbr *bbr = inet_csk_ca(sk);

	bbr->prior_cwnd = 0;
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	bbr->rtt_cnt = 0;
	bbr->next_rtt_delivered = 0;
	bbr->prev_ca_state = TCP_CA_Open;
	bbr->packet_conservation = 0;

	bbr->probe_rtt_done_stamp = 0;
	bbr->probe_rtt_round_done = 0;
	bbr->min_rtt_us = tcp_min_rtt(tp);
	bbr->min_rtt_stamp = tcp_jiffies32;

	minmax_reset(&bbr->bw, bbr->rtt_cnt, 0);  /* init max bw to 0 */

	bbr->has_seen_rtt = 0;
	bbr_init_pacing_rate_from_rtt(sk);

	bbr->round_start = 0;
	bbr->idle_restart = 0;
	bbr->full_bw_reached = 0;
	bbr->full_bw = 0;
	bbr->full_bw_cnt = 0;
	bbr->cycle_mstamp = 0;
	bbr->cycle_idx = 0;
	bbr_reset_lt_bw_sampling(sk);
	bbr_reset_startup_mode(sk);

	bbr->ack_epoch_mstamp = tp->tcp_mstamp;
	bbr->ack_epoch_acked = 0;
	bbr->extra_acked_win_rtts = 0;
	bbr->extra_acked_win_idx = 0;
	bbr->extra_acked[0] = 0;
	bbr->extra_acked[1] = 0;

	cmpxchg(&sk->sk_pacing_status, SK_PACING_NONE, SK_PACING_NEEDED);
}