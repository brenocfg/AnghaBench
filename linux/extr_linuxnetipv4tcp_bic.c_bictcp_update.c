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
typedef  unsigned int u32 ;
struct bictcp {unsigned int last_cwnd; void* last_time; scalar_t__ epoch_start; unsigned int cnt; unsigned int last_max_cwnd; int delayed_ack; } ;
typedef  int s32 ;
typedef  unsigned int __u32 ;

/* Variables and functions */
 int ACK_RATIO_SHIFT ; 
 unsigned int BICTCP_B ; 
 int HZ ; 
 unsigned int low_window ; 
 unsigned int max_increment ; 
 unsigned int smooth_part ; 
 void* tcp_jiffies32 ; 

__attribute__((used)) static inline void bictcp_update(struct bictcp *ca, u32 cwnd)
{
	if (ca->last_cwnd == cwnd &&
	    (s32)(tcp_jiffies32 - ca->last_time) <= HZ / 32)
		return;

	ca->last_cwnd = cwnd;
	ca->last_time = tcp_jiffies32;

	if (ca->epoch_start == 0) /* record the beginning of an epoch */
		ca->epoch_start = tcp_jiffies32;

	/* start off normal */
	if (cwnd <= low_window) {
		ca->cnt = cwnd;
		return;
	}

	/* binary increase */
	if (cwnd < ca->last_max_cwnd) {
		__u32	dist = (ca->last_max_cwnd - cwnd)
			/ BICTCP_B;

		if (dist > max_increment)
			/* linear increase */
			ca->cnt = cwnd / max_increment;
		else if (dist <= 1U)
			/* binary search increase */
			ca->cnt = (cwnd * smooth_part) / BICTCP_B;
		else
			/* binary search increase */
			ca->cnt = cwnd / dist;
	} else {
		/* slow start AMD linear increase */
		if (cwnd < ca->last_max_cwnd + BICTCP_B)
			/* slow start */
			ca->cnt = (cwnd * smooth_part) / BICTCP_B;
		else if (cwnd < ca->last_max_cwnd + max_increment*(BICTCP_B-1))
			/* slow start */
			ca->cnt = (cwnd * (BICTCP_B-1))
				/ (cwnd - ca->last_max_cwnd);
		else
			/* linear increase */
			ca->cnt = cwnd / max_increment;
	}

	/* if in slow start or link utilization is very low */
	if (ca->last_max_cwnd == 0) {
		if (ca->cnt > 20) /* increase cwnd 5% per RTT */
			ca->cnt = 20;
	}

	ca->cnt = (ca->cnt << ACK_RATIO_SHIFT) / ca->delayed_ack;
	if (ca->cnt == 0)			/* cannot be zero */
		ca->cnt = 1;
}