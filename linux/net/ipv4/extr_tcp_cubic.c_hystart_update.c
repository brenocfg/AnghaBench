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
struct tcp_sock {int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_ssthresh; } ;
struct sock {int dummy; } ;
struct bictcp {int found; scalar_t__ last_ack; scalar_t__ round_start; scalar_t__ delay_min; scalar_t__ sample_cnt; scalar_t__ curr_rtt; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int HYSTART_ACK_TRAIN ; 
 int HYSTART_DELAY ; 
 scalar_t__ HYSTART_DELAY_THRESH (int) ; 
 scalar_t__ HYSTART_MIN_SAMPLES ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHYSTARTDELAYCWND ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHYSTARTDELAYDETECT ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHYSTARTTRAINCWND ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHYSTARTTRAINDETECT ; 
 int /*<<< orphan*/  NET_ADD_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bictcp_clock () ; 
 scalar_t__ hystart_ack_delta ; 
 int hystart_detect ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void hystart_update(struct sock *sk, u32 delay)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bictcp *ca = inet_csk_ca(sk);

	if (ca->found & hystart_detect)
		return;

	if (hystart_detect & HYSTART_ACK_TRAIN) {
		u32 now = bictcp_clock();

		/* first detection parameter - ack-train detection */
		if ((s32)(now - ca->last_ack) <= hystart_ack_delta) {
			ca->last_ack = now;
			if ((s32)(now - ca->round_start) > ca->delay_min >> 4) {
				ca->found |= HYSTART_ACK_TRAIN;
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTTRAINDETECT);
				NET_ADD_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTTRAINCWND,
					      tp->snd_cwnd);
				tp->snd_ssthresh = tp->snd_cwnd;
			}
		}
	}

	if (hystart_detect & HYSTART_DELAY) {
		/* obtain the minimum delay of more than sampling packets */
		if (ca->sample_cnt < HYSTART_MIN_SAMPLES) {
			if (ca->curr_rtt == 0 || ca->curr_rtt > delay)
				ca->curr_rtt = delay;

			ca->sample_cnt++;
		} else {
			if (ca->curr_rtt > ca->delay_min +
			    HYSTART_DELAY_THRESH(ca->delay_min >> 3)) {
				ca->found |= HYSTART_DELAY;
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTDELAYDETECT);
				NET_ADD_STATS(sock_net(sk),
					      LINUX_MIB_TCPHYSTARTDELAYCWND,
					      tp->snd_cwnd);
				tp->snd_ssthresh = tp->snd_cwnd;
			}
		}
	}
}