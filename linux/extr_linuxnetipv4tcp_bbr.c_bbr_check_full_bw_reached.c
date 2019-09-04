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
typedef  int u32 ;
struct sock {int dummy; } ;
struct rate_sample {scalar_t__ is_app_limited; } ;
struct bbr {int full_bw; scalar_t__ full_bw_cnt; int full_bw_reached; int /*<<< orphan*/  round_start; } ;

/* Variables and functions */
 int BBR_SCALE ; 
 scalar_t__ bbr_full_bw_cnt ; 
 scalar_t__ bbr_full_bw_reached (struct sock*) ; 
 int bbr_full_bw_thresh ; 
 int bbr_max_bw (struct sock*) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void bbr_check_full_bw_reached(struct sock *sk,
				      const struct rate_sample *rs)
{
	struct bbr *bbr = inet_csk_ca(sk);
	u32 bw_thresh;

	if (bbr_full_bw_reached(sk) || !bbr->round_start || rs->is_app_limited)
		return;

	bw_thresh = (u64)bbr->full_bw * bbr_full_bw_thresh >> BBR_SCALE;
	if (bbr_max_bw(sk) >= bw_thresh) {
		bbr->full_bw = bbr_max_bw(sk);
		bbr->full_bw_cnt = 0;
		return;
	}
	++bbr->full_bw_cnt;
	bbr->full_bw_reached = bbr->full_bw_cnt >= bbr_full_bw_cnt;
}