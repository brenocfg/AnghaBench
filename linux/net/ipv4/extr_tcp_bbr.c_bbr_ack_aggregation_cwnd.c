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

/* Variables and functions */
 int BBR_SCALE ; 
 int BW_UNIT ; 
 scalar_t__ bbr_bw (struct sock*) ; 
 int bbr_extra_acked (struct sock*) ; 
 int bbr_extra_acked_gain ; 
 int bbr_extra_acked_max_us ; 
 scalar_t__ bbr_full_bw_reached (struct sock*) ; 
 int min (int,int) ; 

__attribute__((used)) static u32 bbr_ack_aggregation_cwnd(struct sock *sk)
{
	u32 max_aggr_cwnd, aggr_cwnd = 0;

	if (bbr_extra_acked_gain && bbr_full_bw_reached(sk)) {
		max_aggr_cwnd = ((u64)bbr_bw(sk) * bbr_extra_acked_max_us)
				/ BW_UNIT;
		aggr_cwnd = (bbr_extra_acked_gain * bbr_extra_acked(sk))
			     >> BBR_SCALE;
		aggr_cwnd = min(aggr_cwnd, max_aggr_cwnd);
	}

	return aggr_cwnd;
}