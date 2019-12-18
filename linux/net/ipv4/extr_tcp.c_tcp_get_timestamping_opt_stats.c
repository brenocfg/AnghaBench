#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct tcp_sock {unsigned long data_segs_out; unsigned long total_retrans; int snd_cwnd; int reordering; int snd_ssthresh; int delivered; int delivered_ce; int write_seq; int snd_una; unsigned long bytes_sent; unsigned long bytes_retrans; int dsack_dups; int reord_seen; int srtt_us; int /*<<< orphan*/  rate_app_limited; } ;
struct tcp_info {unsigned long tcpi_busy_time; unsigned long tcpi_rwnd_limited; unsigned long tcpi_sndbuf_limited; } ;
struct sock {int /*<<< orphan*/  sk_pacing_rate; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int icsk_retransmits; int icsk_ca_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_NLA_BUSY ; 
 int /*<<< orphan*/  TCP_NLA_BYTES_RETRANS ; 
 int /*<<< orphan*/  TCP_NLA_BYTES_SENT ; 
 int /*<<< orphan*/  TCP_NLA_CA_STATE ; 
 int /*<<< orphan*/  TCP_NLA_DATA_SEGS_OUT ; 
 int /*<<< orphan*/  TCP_NLA_DELIVERED ; 
 int /*<<< orphan*/  TCP_NLA_DELIVERED_CE ; 
 int /*<<< orphan*/  TCP_NLA_DELIVERY_RATE ; 
 int /*<<< orphan*/  TCP_NLA_DELIVERY_RATE_APP_LMT ; 
 int /*<<< orphan*/  TCP_NLA_DSACK_DUPS ; 
 int /*<<< orphan*/  TCP_NLA_MIN_RTT ; 
 int /*<<< orphan*/  TCP_NLA_PACING_RATE ; 
 int /*<<< orphan*/  TCP_NLA_PAD ; 
 int /*<<< orphan*/  TCP_NLA_RECUR_RETRANS ; 
 int /*<<< orphan*/  TCP_NLA_REORDERING ; 
 int /*<<< orphan*/  TCP_NLA_REORD_SEEN ; 
 int /*<<< orphan*/  TCP_NLA_RWND_LIMITED ; 
 int /*<<< orphan*/  TCP_NLA_SNDBUF_LIMITED ; 
 int /*<<< orphan*/  TCP_NLA_SNDQ_SIZE ; 
 int /*<<< orphan*/  TCP_NLA_SND_CWND ; 
 int /*<<< orphan*/  TCP_NLA_SND_SSTHRESH ; 
 int /*<<< orphan*/  TCP_NLA_SRTT ; 
 int /*<<< orphan*/  TCP_NLA_TOTAL_RETRANS ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 unsigned long tcp_compute_delivery_rate (struct tcp_sock const*) ; 
 int /*<<< orphan*/  tcp_get_info_chrono_stats (struct tcp_sock const*,struct tcp_info*) ; 
 int tcp_min_rtt (struct tcp_sock const*) ; 
 int /*<<< orphan*/  tcp_opt_stats_get_size () ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 

struct sk_buff *tcp_get_timestamping_opt_stats(const struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *stats;
	struct tcp_info info;
	unsigned long rate;
	u64 rate64;

	stats = alloc_skb(tcp_opt_stats_get_size(), GFP_ATOMIC);
	if (!stats)
		return NULL;

	tcp_get_info_chrono_stats(tp, &info);
	nla_put_u64_64bit(stats, TCP_NLA_BUSY,
			  info.tcpi_busy_time, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_RWND_LIMITED,
			  info.tcpi_rwnd_limited, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_SNDBUF_LIMITED,
			  info.tcpi_sndbuf_limited, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_DATA_SEGS_OUT,
			  tp->data_segs_out, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_TOTAL_RETRANS,
			  tp->total_retrans, TCP_NLA_PAD);

	rate = READ_ONCE(sk->sk_pacing_rate);
	rate64 = (rate != ~0UL) ? rate : ~0ULL;
	nla_put_u64_64bit(stats, TCP_NLA_PACING_RATE, rate64, TCP_NLA_PAD);

	rate64 = tcp_compute_delivery_rate(tp);
	nla_put_u64_64bit(stats, TCP_NLA_DELIVERY_RATE, rate64, TCP_NLA_PAD);

	nla_put_u32(stats, TCP_NLA_SND_CWND, tp->snd_cwnd);
	nla_put_u32(stats, TCP_NLA_REORDERING, tp->reordering);
	nla_put_u32(stats, TCP_NLA_MIN_RTT, tcp_min_rtt(tp));

	nla_put_u8(stats, TCP_NLA_RECUR_RETRANS, inet_csk(sk)->icsk_retransmits);
	nla_put_u8(stats, TCP_NLA_DELIVERY_RATE_APP_LMT, !!tp->rate_app_limited);
	nla_put_u32(stats, TCP_NLA_SND_SSTHRESH, tp->snd_ssthresh);
	nla_put_u32(stats, TCP_NLA_DELIVERED, tp->delivered);
	nla_put_u32(stats, TCP_NLA_DELIVERED_CE, tp->delivered_ce);

	nla_put_u32(stats, TCP_NLA_SNDQ_SIZE, tp->write_seq - tp->snd_una);
	nla_put_u8(stats, TCP_NLA_CA_STATE, inet_csk(sk)->icsk_ca_state);

	nla_put_u64_64bit(stats, TCP_NLA_BYTES_SENT, tp->bytes_sent,
			  TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_BYTES_RETRANS, tp->bytes_retrans,
			  TCP_NLA_PAD);
	nla_put_u32(stats, TCP_NLA_DSACK_DUPS, tp->dsack_dups);
	nla_put_u32(stats, TCP_NLA_REORD_SEEN, tp->reord_seen);
	nla_put_u32(stats, TCP_NLA_SRTT, tp->srtt_us >> 3);

	return stats;
}