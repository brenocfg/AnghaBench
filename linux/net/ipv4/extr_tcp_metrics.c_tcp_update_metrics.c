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
typedef  int u32 ;
struct tcp_sock {unsigned long srtt_us; int mdev_us; int snd_cwnd; int snd_ssthresh; int reordering; } ;
struct tcp_metrics_block {int /*<<< orphan*/  tcpm_stamp; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int sysctl_tcp_reordering; scalar_t__ sysctl_tcp_nometrics_save; } ;
struct net {TYPE_1__ ipv4; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; scalar_t__ icsk_backoff; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCP_CA_Open ; 
 int /*<<< orphan*/  TCP_METRIC_CWND ; 
 int /*<<< orphan*/  TCP_METRIC_REORDERING ; 
 int /*<<< orphan*/  TCP_METRIC_RTT ; 
 int /*<<< orphan*/  TCP_METRIC_RTTVAR ; 
 int /*<<< orphan*/  TCP_METRIC_SSTHRESH ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 int max (int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_dst_confirm (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 struct tcp_metrics_block* tcp_get_metrics (struct sock*,struct dst_entry*,int) ; 
 scalar_t__ tcp_in_initial_slowstart (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_in_slow_start (struct tcp_sock*) ; 
 void* tcp_metric_get (struct tcp_metrics_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_metric_locked (struct tcp_metrics_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_metric_set (struct tcp_metrics_block*,int /*<<< orphan*/ ,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_update_metrics(struct sock *sk)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	struct dst_entry *dst = __sk_dst_get(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct net *net = sock_net(sk);
	struct tcp_metrics_block *tm;
	unsigned long rtt;
	u32 val;
	int m;

	sk_dst_confirm(sk);
	if (net->ipv4.sysctl_tcp_nometrics_save || !dst)
		return;

	rcu_read_lock();
	if (icsk->icsk_backoff || !tp->srtt_us) {
		/* This session failed to estimate rtt. Why?
		 * Probably, no packets returned in time.  Reset our
		 * results.
		 */
		tm = tcp_get_metrics(sk, dst, false);
		if (tm && !tcp_metric_locked(tm, TCP_METRIC_RTT))
			tcp_metric_set(tm, TCP_METRIC_RTT, 0);
		goto out_unlock;
	} else
		tm = tcp_get_metrics(sk, dst, true);

	if (!tm)
		goto out_unlock;

	rtt = tcp_metric_get(tm, TCP_METRIC_RTT);
	m = rtt - tp->srtt_us;

	/* If newly calculated rtt larger than stored one, store new
	 * one. Otherwise, use EWMA. Remember, rtt overestimation is
	 * always better than underestimation.
	 */
	if (!tcp_metric_locked(tm, TCP_METRIC_RTT)) {
		if (m <= 0)
			rtt = tp->srtt_us;
		else
			rtt -= (m >> 3);
		tcp_metric_set(tm, TCP_METRIC_RTT, rtt);
	}

	if (!tcp_metric_locked(tm, TCP_METRIC_RTTVAR)) {
		unsigned long var;

		if (m < 0)
			m = -m;

		/* Scale deviation to rttvar fixed point */
		m >>= 1;
		if (m < tp->mdev_us)
			m = tp->mdev_us;

		var = tcp_metric_get(tm, TCP_METRIC_RTTVAR);
		if (m >= var)
			var = m;
		else
			var -= (var - m) >> 2;

		tcp_metric_set(tm, TCP_METRIC_RTTVAR, var);
	}

	if (tcp_in_initial_slowstart(tp)) {
		/* Slow start still did not finish. */
		if (!tcp_metric_locked(tm, TCP_METRIC_SSTHRESH)) {
			val = tcp_metric_get(tm, TCP_METRIC_SSTHRESH);
			if (val && (tp->snd_cwnd >> 1) > val)
				tcp_metric_set(tm, TCP_METRIC_SSTHRESH,
					       tp->snd_cwnd >> 1);
		}
		if (!tcp_metric_locked(tm, TCP_METRIC_CWND)) {
			val = tcp_metric_get(tm, TCP_METRIC_CWND);
			if (tp->snd_cwnd > val)
				tcp_metric_set(tm, TCP_METRIC_CWND,
					       tp->snd_cwnd);
		}
	} else if (!tcp_in_slow_start(tp) &&
		   icsk->icsk_ca_state == TCP_CA_Open) {
		/* Cong. avoidance phase, cwnd is reliable. */
		if (!tcp_metric_locked(tm, TCP_METRIC_SSTHRESH))
			tcp_metric_set(tm, TCP_METRIC_SSTHRESH,
				       max(tp->snd_cwnd >> 1, tp->snd_ssthresh));
		if (!tcp_metric_locked(tm, TCP_METRIC_CWND)) {
			val = tcp_metric_get(tm, TCP_METRIC_CWND);
			tcp_metric_set(tm, TCP_METRIC_CWND, (val + tp->snd_cwnd) >> 1);
		}
	} else {
		/* Else slow start did not finish, cwnd is non-sense,
		 * ssthresh may be also invalid.
		 */
		if (!tcp_metric_locked(tm, TCP_METRIC_CWND)) {
			val = tcp_metric_get(tm, TCP_METRIC_CWND);
			tcp_metric_set(tm, TCP_METRIC_CWND,
				       (val + tp->snd_ssthresh) >> 1);
		}
		if (!tcp_metric_locked(tm, TCP_METRIC_SSTHRESH)) {
			val = tcp_metric_get(tm, TCP_METRIC_SSTHRESH);
			if (val && tp->snd_ssthresh > val)
				tcp_metric_set(tm, TCP_METRIC_SSTHRESH,
					       tp->snd_ssthresh);
		}
		if (!tcp_metric_locked(tm, TCP_METRIC_REORDERING)) {
			val = tcp_metric_get(tm, TCP_METRIC_REORDERING);
			if (val < tp->reordering &&
			    tp->reordering != net->ipv4.sysctl_tcp_reordering)
				tcp_metric_set(tm, TCP_METRIC_REORDERING,
					       tp->reordering);
		}
	}
	tm->tcpm_stamp = jiffies;
out_unlock:
	rcu_read_unlock();
}