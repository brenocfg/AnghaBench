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
struct sock {int dummy; } ;
struct illinois {scalar_t__ base_rtt; scalar_t__ max_rtt; int /*<<< orphan*/  sum_rtt; int /*<<< orphan*/  cnt_rtt; int /*<<< orphan*/  acked; } ;
struct ack_sample {scalar_t__ rtt_us; int /*<<< orphan*/  pkts_acked; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ RTT_MAX ; 
 struct illinois* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void tcp_illinois_acked(struct sock *sk, const struct ack_sample *sample)
{
	struct illinois *ca = inet_csk_ca(sk);
	s32 rtt_us = sample->rtt_us;

	ca->acked = sample->pkts_acked;

	/* dup ack, no rtt sample */
	if (rtt_us < 0)
		return;

	/* ignore bogus values, this prevents wraparound in alpha math */
	if (rtt_us > RTT_MAX)
		rtt_us = RTT_MAX;

	/* keep track of minimum RTT seen so far */
	if (ca->base_rtt > rtt_us)
		ca->base_rtt = rtt_us;

	/* and max */
	if (ca->max_rtt < rtt_us)
		ca->max_rtt = rtt_us;

	++ca->cnt_rtt;
	ca->sum_rtt += rtt_us;
}