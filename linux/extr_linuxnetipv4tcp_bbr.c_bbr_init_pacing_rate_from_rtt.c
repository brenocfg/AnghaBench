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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {int srtt_us; scalar_t__ snd_cwnd; } ;
struct sock {int /*<<< orphan*/  sk_pacing_rate; } ;
struct bbr {int has_seen_rtt; } ;

/* Variables and functions */
 int BW_UNIT ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 int /*<<< orphan*/  bbr_bw_to_pacing_rate (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbr_high_gain ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bbr_init_pacing_rate_from_rtt(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bbr *bbr = inet_csk_ca(sk);
	u64 bw;
	u32 rtt_us;

	if (tp->srtt_us) {		/* any RTT sample yet? */
		rtt_us = max(tp->srtt_us >> 3, 1U);
		bbr->has_seen_rtt = 1;
	} else {			 /* no RTT sample yet */
		rtt_us = USEC_PER_MSEC;	 /* use nominal default RTT */
	}
	bw = (u64)tp->snd_cwnd * BW_UNIT;
	do_div(bw, rtt_us);
	sk->sk_pacing_rate = bbr_bw_to_pacing_rate(sk, bw, bbr_high_gain);
}