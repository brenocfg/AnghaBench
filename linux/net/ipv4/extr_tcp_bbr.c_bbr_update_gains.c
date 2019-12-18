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
struct bbr {int mode; size_t cycle_idx; void* cwnd_gain; void* pacing_gain; int /*<<< orphan*/  lt_use_bw; } ;

/* Variables and functions */
#define  BBR_DRAIN 131 
#define  BBR_PROBE_BW 130 
#define  BBR_PROBE_RTT 129 
#define  BBR_STARTUP 128 
 void* BBR_UNIT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 void* bbr_cwnd_gain ; 
 void* bbr_drain_gain ; 
 void* bbr_high_gain ; 
 void** bbr_pacing_gain ; 
 struct bbr* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void bbr_update_gains(struct sock *sk)
{
	struct bbr *bbr = inet_csk_ca(sk);

	switch (bbr->mode) {
	case BBR_STARTUP:
		bbr->pacing_gain = bbr_high_gain;
		bbr->cwnd_gain	 = bbr_high_gain;
		break;
	case BBR_DRAIN:
		bbr->pacing_gain = bbr_drain_gain;	/* slow, to drain */
		bbr->cwnd_gain	 = bbr_high_gain;	/* keep cwnd */
		break;
	case BBR_PROBE_BW:
		bbr->pacing_gain = (bbr->lt_use_bw ?
				    BBR_UNIT :
				    bbr_pacing_gain[bbr->cycle_idx]);
		bbr->cwnd_gain	 = bbr_cwnd_gain;
		break;
	case BBR_PROBE_RTT:
		bbr->pacing_gain = BBR_UNIT;
		bbr->cwnd_gain	 = BBR_UNIT;
		break;
	default:
		WARN_ONCE(1, "BBR bad mode: %u\n", bbr->mode);
		break;
	}
}