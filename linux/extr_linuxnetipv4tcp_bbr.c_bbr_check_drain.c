#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct rate_sample {int dummy; } ;
struct bbr {scalar_t__ mode; int /*<<< orphan*/  cwnd_gain; int /*<<< orphan*/  pacing_gain; } ;
struct TYPE_3__ {scalar_t__ snd_ssthresh; } ;

/* Variables and functions */
 scalar_t__ BBR_DRAIN ; 
 scalar_t__ BBR_STARTUP ; 
 int /*<<< orphan*/  BBR_UNIT ; 
 int /*<<< orphan*/  bbr_drain_gain ; 
 scalar_t__ bbr_full_bw_reached (struct sock*) ; 
 int /*<<< orphan*/  bbr_high_gain ; 
 int /*<<< orphan*/  bbr_max_bw (struct sock*) ; 
 int /*<<< orphan*/  bbr_reset_probe_bw_mode (struct sock*) ; 
 scalar_t__ bbr_target_cwnd (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 scalar_t__ tcp_packets_in_flight (TYPE_1__*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bbr_check_drain(struct sock *sk, const struct rate_sample *rs)
{
	struct bbr *bbr = inet_csk_ca(sk);

	if (bbr->mode == BBR_STARTUP && bbr_full_bw_reached(sk)) {
		bbr->mode = BBR_DRAIN;	/* drain queue we created */
		bbr->pacing_gain = bbr_drain_gain;	/* pace slow to drain */
		bbr->cwnd_gain = bbr_high_gain;	/* maintain cwnd */
		tcp_sk(sk)->snd_ssthresh =
				bbr_target_cwnd(sk, bbr_max_bw(sk), BBR_UNIT);
	}	/* fall through to check if in-flight is already small: */
	if (bbr->mode == BBR_DRAIN &&
	    tcp_packets_in_flight(tcp_sk(sk)) <=
	    bbr_target_cwnd(sk, bbr_max_bw(sk), BBR_UNIT))
		bbr_reset_probe_bw_mode(sk);  /* we estimate queue is drained */
}