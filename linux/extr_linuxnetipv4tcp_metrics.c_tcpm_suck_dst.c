#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int exp; scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__ cookie; scalar_t__ try_exp; scalar_t__ syn_loss; scalar_t__ mss; } ;
struct tcp_metrics_block {int tcpm_lock; int* tcpm_vals; TYPE_2__ tcpm_fastopen; int /*<<< orphan*/  tcpm_stamp; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_CWND ; 
 int /*<<< orphan*/  RTAX_REORDERING ; 
 int /*<<< orphan*/  RTAX_RTT ; 
 int /*<<< orphan*/  RTAX_RTTVAR ; 
 int /*<<< orphan*/  RTAX_SSTHRESH ; 
 int TCP_METRIC_CWND ; 
 int TCP_METRIC_REORDERING ; 
 int TCP_METRIC_RTT ; 
 int TCP_METRIC_RTTVAR ; 
 int TCP_METRIC_SSTHRESH ; 
 int USEC_PER_MSEC ; 
 scalar_t__ dst_metric_locked (struct dst_entry const*,int /*<<< orphan*/ ) ; 
 void* dst_metric_raw (struct dst_entry const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void tcpm_suck_dst(struct tcp_metrics_block *tm,
			  const struct dst_entry *dst,
			  bool fastopen_clear)
{
	u32 msval;
	u32 val;

	tm->tcpm_stamp = jiffies;

	val = 0;
	if (dst_metric_locked(dst, RTAX_RTT))
		val |= 1 << TCP_METRIC_RTT;
	if (dst_metric_locked(dst, RTAX_RTTVAR))
		val |= 1 << TCP_METRIC_RTTVAR;
	if (dst_metric_locked(dst, RTAX_SSTHRESH))
		val |= 1 << TCP_METRIC_SSTHRESH;
	if (dst_metric_locked(dst, RTAX_CWND))
		val |= 1 << TCP_METRIC_CWND;
	if (dst_metric_locked(dst, RTAX_REORDERING))
		val |= 1 << TCP_METRIC_REORDERING;
	tm->tcpm_lock = val;

	msval = dst_metric_raw(dst, RTAX_RTT);
	tm->tcpm_vals[TCP_METRIC_RTT] = msval * USEC_PER_MSEC;

	msval = dst_metric_raw(dst, RTAX_RTTVAR);
	tm->tcpm_vals[TCP_METRIC_RTTVAR] = msval * USEC_PER_MSEC;
	tm->tcpm_vals[TCP_METRIC_SSTHRESH] = dst_metric_raw(dst, RTAX_SSTHRESH);
	tm->tcpm_vals[TCP_METRIC_CWND] = dst_metric_raw(dst, RTAX_CWND);
	tm->tcpm_vals[TCP_METRIC_REORDERING] = dst_metric_raw(dst, RTAX_REORDERING);
	if (fastopen_clear) {
		tm->tcpm_fastopen.mss = 0;
		tm->tcpm_fastopen.syn_loss = 0;
		tm->tcpm_fastopen.try_exp = 0;
		tm->tcpm_fastopen.cookie.exp = false;
		tm->tcpm_fastopen.cookie.len = 0;
	}
}