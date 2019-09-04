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
typedef  int u32 ;
struct tcp_sock {scalar_t__ snd_cwnd; } ;
struct sock {int dummy; } ;
struct bictcp {int delay_min; scalar_t__ epoch_start; } ;
struct ack_sample {int rtt_us; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int USEC_PER_MSEC ; 
 scalar_t__ hystart ; 
 scalar_t__ hystart_low_window ; 
 int /*<<< orphan*/  hystart_update (struct sock*,int) ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 
 scalar_t__ tcp_in_slow_start (struct tcp_sock const*) ; 
 scalar_t__ tcp_jiffies32 ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bictcp_acked(struct sock *sk, const struct ack_sample *sample)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct bictcp *ca = inet_csk_ca(sk);
	u32 delay;

	/* Some calls are for duplicates without timetamps */
	if (sample->rtt_us < 0)
		return;

	/* Discard delay samples right after fast recovery */
	if (ca->epoch_start && (s32)(tcp_jiffies32 - ca->epoch_start) < HZ)
		return;

	delay = (sample->rtt_us << 3) / USEC_PER_MSEC;
	if (delay == 0)
		delay = 1;

	/* first time call or link delay decreases */
	if (ca->delay_min == 0 || ca->delay_min > delay)
		ca->delay_min = delay;

	/* hystart triggers when cwnd is larger than some threshold */
	if (hystart && tcp_in_slow_start(tp) &&
	    tp->snd_cwnd >= hystart_low_window)
		hystart_update(sk, delay);
}