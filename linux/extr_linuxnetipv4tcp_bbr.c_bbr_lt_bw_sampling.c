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
typedef  int u64 ;
typedef  unsigned int u32 ;
struct tcp_sock {unsigned int lost; unsigned int delivered; int /*<<< orphan*/  delivered_mstamp; } ;
struct sock {int dummy; } ;
struct rate_sample {int /*<<< orphan*/  losses; scalar_t__ is_app_limited; } ;
struct bbr {scalar_t__ mode; scalar_t__ lt_rtt_cnt; int lt_is_sampling; unsigned int lt_last_lost; unsigned int lt_last_delivered; unsigned int lt_last_stamp; scalar_t__ round_start; scalar_t__ lt_use_bw; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ BBR_PROBE_BW ; 
 unsigned int BBR_SCALE ; 
 int BW_UNIT ; 
 unsigned int USEC_PER_MSEC ; 
 int /*<<< orphan*/  bbr_lt_bw_interval_done (struct sock*,int) ; 
 scalar_t__ bbr_lt_bw_max_rtts ; 
 int bbr_lt_intvl_min_rtts ; 
 unsigned int bbr_lt_loss_thresh ; 
 int /*<<< orphan*/  bbr_reset_lt_bw_sampling (struct sock*) ; 
 int /*<<< orphan*/  bbr_reset_lt_bw_sampling_interval (struct sock*) ; 
 int /*<<< orphan*/  bbr_reset_probe_bw_mode (struct sock*) ; 
 unsigned int div_u64 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bbr_lt_bw_sampling(struct sock *sk, const struct rate_sample *rs)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bbr *bbr = inet_csk_ca(sk);
	u32 lost, delivered;
	u64 bw;
	u32 t;

	if (bbr->lt_use_bw) {	/* already using long-term rate, lt_bw? */
		if (bbr->mode == BBR_PROBE_BW && bbr->round_start &&
		    ++bbr->lt_rtt_cnt >= bbr_lt_bw_max_rtts) {
			bbr_reset_lt_bw_sampling(sk);    /* stop using lt_bw */
			bbr_reset_probe_bw_mode(sk);  /* restart gain cycling */
		}
		return;
	}

	/* Wait for the first loss before sampling, to let the policer exhaust
	 * its tokens and estimate the steady-state rate allowed by the policer.
	 * Starting samples earlier includes bursts that over-estimate the bw.
	 */
	if (!bbr->lt_is_sampling) {
		if (!rs->losses)
			return;
		bbr_reset_lt_bw_sampling_interval(sk);
		bbr->lt_is_sampling = true;
	}

	/* To avoid underestimates, reset sampling if we run out of data. */
	if (rs->is_app_limited) {
		bbr_reset_lt_bw_sampling(sk);
		return;
	}

	if (bbr->round_start)
		bbr->lt_rtt_cnt++;	/* count round trips in this interval */
	if (bbr->lt_rtt_cnt < bbr_lt_intvl_min_rtts)
		return;		/* sampling interval needs to be longer */
	if (bbr->lt_rtt_cnt > 4 * bbr_lt_intvl_min_rtts) {
		bbr_reset_lt_bw_sampling(sk);  /* interval is too long */
		return;
	}

	/* End sampling interval when a packet is lost, so we estimate the
	 * policer tokens were exhausted. Stopping the sampling before the
	 * tokens are exhausted under-estimates the policed rate.
	 */
	if (!rs->losses)
		return;

	/* Calculate packets lost and delivered in sampling interval. */
	lost = tp->lost - bbr->lt_last_lost;
	delivered = tp->delivered - bbr->lt_last_delivered;
	/* Is loss rate (lost/delivered) >= lt_loss_thresh? If not, wait. */
	if (!delivered || (lost << BBR_SCALE) < bbr_lt_loss_thresh * delivered)
		return;

	/* Find average delivery rate in this sampling interval. */
	t = div_u64(tp->delivered_mstamp, USEC_PER_MSEC) - bbr->lt_last_stamp;
	if ((s32)t < 1)
		return;		/* interval is less than one ms, so wait */
	/* Check if can multiply without overflow */
	if (t >= ~0U / USEC_PER_MSEC) {
		bbr_reset_lt_bw_sampling(sk);  /* interval too long; reset */
		return;
	}
	t *= USEC_PER_MSEC;
	bw = (u64)delivered * BW_UNIT;
	do_div(bw, t);
	bbr_lt_bw_interval_done(sk, bw);
}