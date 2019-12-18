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
struct bpf_tcp_sock {int snd_cwnd; int srtt_us; int rtt_min; int snd_ssthresh; int rcv_nxt; int snd_nxt; int snd_una; int mss_cache; int ecn_flags; int rate_delivered; int rate_interval_us; int packets_out; int retrans_out; int total_retrans; int segs_in; int data_segs_in; int segs_out; int data_segs_out; int lost_out; int sacked_out; int /*<<< orphan*/  bytes_acked; int /*<<< orphan*/  bytes_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_tp(const struct bpf_tcp_sock *tp)
{
	printf("snd_cwnd:%u srtt_us:%u rtt_min:%u snd_ssthresh:%u rcv_nxt:%u "
	       "snd_nxt:%u snd:una:%u mss_cache:%u ecn_flags:%u "
	       "rate_delivered:%u rate_interval_us:%u packets_out:%u "
	       "retrans_out:%u total_retrans:%u segs_in:%u data_segs_in:%u "
	       "segs_out:%u data_segs_out:%u lost_out:%u sacked_out:%u "
	       "bytes_received:%llu bytes_acked:%llu\n",
	       tp->snd_cwnd, tp->srtt_us, tp->rtt_min, tp->snd_ssthresh,
	       tp->rcv_nxt, tp->snd_nxt, tp->snd_una, tp->mss_cache,
	       tp->ecn_flags, tp->rate_delivered, tp->rate_interval_us,
	       tp->packets_out, tp->retrans_out, tp->total_retrans,
	       tp->segs_in, tp->data_segs_in, tp->segs_out,
	       tp->data_segs_out, tp->lost_out, tp->sacked_out,
	       tp->bytes_received, tp->bytes_acked);
}