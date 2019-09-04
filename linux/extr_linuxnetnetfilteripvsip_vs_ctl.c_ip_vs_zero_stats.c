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
struct TYPE_3__ {int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; int /*<<< orphan*/  outpkts; int /*<<< orphan*/  inpkts; int /*<<< orphan*/  conns; } ;
struct TYPE_4__ {int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; int /*<<< orphan*/  outpkts; int /*<<< orphan*/  inpkts; int /*<<< orphan*/  conns; } ;
struct ip_vs_stats {int /*<<< orphan*/  lock; TYPE_1__ kstats; TYPE_2__ kstats0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_zero_estimator (struct ip_vs_stats*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip_vs_zero_stats(struct ip_vs_stats *stats)
{
	spin_lock_bh(&stats->lock);

	/* get current counters as zero point, rates are zeroed */

#define IP_VS_ZERO_STATS_COUNTER(c) stats->kstats0.c = stats->kstats.c

	IP_VS_ZERO_STATS_COUNTER(conns);
	IP_VS_ZERO_STATS_COUNTER(inpkts);
	IP_VS_ZERO_STATS_COUNTER(outpkts);
	IP_VS_ZERO_STATS_COUNTER(inbytes);
	IP_VS_ZERO_STATS_COUNTER(outbytes);

	ip_vs_zero_estimator(stats);

	spin_unlock_bh(&stats->lock);
}