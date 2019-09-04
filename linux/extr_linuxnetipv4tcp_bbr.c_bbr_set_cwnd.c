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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ snd_cwnd; scalar_t__ delivered; scalar_t__ snd_cwnd_clamp; } ;
struct sock {int dummy; } ;
struct rate_sample {int dummy; } ;
struct bbr {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ BBR_PROBE_RTT ; 
 scalar_t__ TCP_INIT_CWND ; 
 scalar_t__ bbr_cwnd_min_target ; 
 scalar_t__ bbr_full_bw_reached (struct sock*) ; 
 scalar_t__ bbr_set_cwnd_to_recover_or_restore (struct sock*,struct rate_sample const*,scalar_t__,scalar_t__*) ; 
 scalar_t__ bbr_target_cwnd (struct sock*,scalar_t__,int) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bbr_set_cwnd(struct sock *sk, const struct rate_sample *rs,
			 u32 acked, u32 bw, int gain)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bbr *bbr = inet_csk_ca(sk);
	u32 cwnd = tp->snd_cwnd, target_cwnd = 0;

	if (!acked)
		goto done;  /* no packet fully ACKed; just apply caps */

	if (bbr_set_cwnd_to_recover_or_restore(sk, rs, acked, &cwnd))
		goto done;

	/* If we're below target cwnd, slow start cwnd toward target cwnd. */
	target_cwnd = bbr_target_cwnd(sk, bw, gain);
	if (bbr_full_bw_reached(sk))  /* only cut cwnd if we filled the pipe */
		cwnd = min(cwnd + acked, target_cwnd);
	else if (cwnd < target_cwnd || tp->delivered < TCP_INIT_CWND)
		cwnd = cwnd + acked;
	cwnd = max(cwnd, bbr_cwnd_min_target);

done:
	tp->snd_cwnd = min(cwnd, tp->snd_cwnd_clamp);	/* apply global cap */
	if (bbr->mode == BBR_PROBE_RTT)  /* drain queue, refresh min_rtt */
		tp->snd_cwnd = min(tp->snd_cwnd, bbr_cwnd_min_target);
}