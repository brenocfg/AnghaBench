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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ snd_cwnd_clamp; scalar_t__ snd_ssthresh; scalar_t__ reordering; scalar_t__ srtt_us; int /*<<< orphan*/  rttvar_us; int /*<<< orphan*/  mdev_max_us; int /*<<< orphan*/  mdev_us; } ;
struct tcp_metrics_block {int dummy; } ;
struct sock {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_rto; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ TCP_INFINITE_SSTHRESH ; 
 int /*<<< orphan*/  TCP_METRIC_CWND ; 
 int /*<<< orphan*/  TCP_METRIC_REORDERING ; 
 int /*<<< orphan*/  TCP_METRIC_RTT ; 
 int /*<<< orphan*/  TCP_METRIC_SSTHRESH ; 
 scalar_t__ TCP_TIMEOUT_FALLBACK ; 
 int USEC_PER_SEC ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  jiffies_to_usecs (scalar_t__) ; 
 scalar_t__ max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_dst_confirm (struct sock*) ; 
 struct tcp_metrics_block* tcp_get_metrics (struct sock*,struct dst_entry*,int) ; 
 scalar_t__ tcp_metric_get (struct tcp_metrics_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_metric_locked (struct tcp_metrics_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_rto_min (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_init_metrics(struct sock *sk)
{
	struct dst_entry *dst = __sk_dst_get(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcp_metrics_block *tm;
	u32 val, crtt = 0; /* cached RTT scaled by 8 */

	sk_dst_confirm(sk);
	if (!dst)
		goto reset;

	rcu_read_lock();
	tm = tcp_get_metrics(sk, dst, true);
	if (!tm) {
		rcu_read_unlock();
		goto reset;
	}

	if (tcp_metric_locked(tm, TCP_METRIC_CWND))
		tp->snd_cwnd_clamp = tcp_metric_get(tm, TCP_METRIC_CWND);

	val = tcp_metric_get(tm, TCP_METRIC_SSTHRESH);
	if (val) {
		tp->snd_ssthresh = val;
		if (tp->snd_ssthresh > tp->snd_cwnd_clamp)
			tp->snd_ssthresh = tp->snd_cwnd_clamp;
	} else {
		/* ssthresh may have been reduced unnecessarily during.
		 * 3WHS. Restore it back to its initial default.
		 */
		tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	}
	val = tcp_metric_get(tm, TCP_METRIC_REORDERING);
	if (val && tp->reordering != val)
		tp->reordering = val;

	crtt = tcp_metric_get(tm, TCP_METRIC_RTT);
	rcu_read_unlock();
reset:
	/* The initial RTT measurement from the SYN/SYN-ACK is not ideal
	 * to seed the RTO for later data packets because SYN packets are
	 * small. Use the per-dst cached values to seed the RTO but keep
	 * the RTT estimator variables intact (e.g., srtt, mdev, rttvar).
	 * Later the RTO will be updated immediately upon obtaining the first
	 * data RTT sample (tcp_rtt_estimator()). Hence the cached RTT only
	 * influences the first RTO but not later RTT estimation.
	 *
	 * But if RTT is not available from the SYN (due to retransmits or
	 * syn cookies) or the cache, force a conservative 3secs timeout.
	 *
	 * A bit of theory. RTT is time passed after "normal" sized packet
	 * is sent until it is ACKed. In normal circumstances sending small
	 * packets force peer to delay ACKs and calculation is correct too.
	 * The algorithm is adaptive and, provided we follow specs, it
	 * NEVER underestimate RTT. BUT! If peer tries to make some clever
	 * tricks sort of "quick acks" for time long enough to decrease RTT
	 * to low value, and then abruptly stops to do it and starts to delay
	 * ACKs, wait for troubles.
	 */
	if (crtt > tp->srtt_us) {
		/* Set RTO like tcp_rtt_estimator(), but from cached RTT. */
		crtt /= 8 * USEC_PER_SEC / HZ;
		inet_csk(sk)->icsk_rto = crtt + max(2 * crtt, tcp_rto_min(sk));
	} else if (tp->srtt_us == 0) {
		/* RFC6298: 5.7 We've failed to get a valid RTT sample from
		 * 3WHS. This is most likely due to retransmission,
		 * including spurious one. Reset the RTO back to 3secs
		 * from the more aggressive 1sec to avoid more spurious
		 * retransmission.
		 */
		tp->rttvar_us = jiffies_to_usecs(TCP_TIMEOUT_FALLBACK);
		tp->mdev_us = tp->mdev_max_us = tp->rttvar_us;

		inet_csk(sk)->icsk_rto = TCP_TIMEOUT_FALLBACK;
	}
}