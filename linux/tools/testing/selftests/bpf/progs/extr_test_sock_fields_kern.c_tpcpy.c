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
struct bpf_tcp_sock {int /*<<< orphan*/  bytes_acked; int /*<<< orphan*/  bytes_received; int /*<<< orphan*/  sacked_out; int /*<<< orphan*/  lost_out; int /*<<< orphan*/  data_segs_out; int /*<<< orphan*/  segs_out; int /*<<< orphan*/  data_segs_in; int /*<<< orphan*/  segs_in; int /*<<< orphan*/  total_retrans; int /*<<< orphan*/  retrans_out; int /*<<< orphan*/  packets_out; int /*<<< orphan*/  rate_interval_us; int /*<<< orphan*/  rate_delivered; int /*<<< orphan*/  ecn_flags; int /*<<< orphan*/  mss_cache; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  rtt_min; int /*<<< orphan*/  srtt_us; int /*<<< orphan*/  snd_cwnd; } ;

/* Variables and functions */

__attribute__((used)) static void tpcpy(struct bpf_tcp_sock *dst,
		  const struct bpf_tcp_sock *src)
{
	dst->snd_cwnd = src->snd_cwnd;
	dst->srtt_us = src->srtt_us;
	dst->rtt_min = src->rtt_min;
	dst->snd_ssthresh = src->snd_ssthresh;
	dst->rcv_nxt = src->rcv_nxt;
	dst->snd_nxt = src->snd_nxt;
	dst->snd_una = src->snd_una;
	dst->mss_cache = src->mss_cache;
	dst->ecn_flags = src->ecn_flags;
	dst->rate_delivered = src->rate_delivered;
	dst->rate_interval_us = src->rate_interval_us;
	dst->packets_out = src->packets_out;
	dst->retrans_out = src->retrans_out;
	dst->total_retrans = src->total_retrans;
	dst->segs_in = src->segs_in;
	dst->data_segs_in = src->data_segs_in;
	dst->segs_out = src->segs_out;
	dst->data_segs_out = src->data_segs_out;
	dst->lost_out = src->lost_out;
	dst->sacked_out = src->sacked_out;
	dst->bytes_received = src->bytes_received;
	dst->bytes_acked = src->bytes_acked;
}