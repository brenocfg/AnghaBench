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
struct TYPE_4__ {scalar_t__ outbytes; scalar_t__ inbytes; scalar_t__ outpkts; scalar_t__ inpkts; scalar_t__ conns; } ;
struct TYPE_3__ {scalar_t__ outbytes; scalar_t__ inbytes; scalar_t__ outpkts; scalar_t__ inpkts; scalar_t__ conns; } ;
struct ip_vs_stats {int /*<<< orphan*/  lock; TYPE_2__ kstats0; TYPE_1__ kstats; } ;
struct ip_vs_kstats {scalar_t__ outbytes; scalar_t__ inbytes; scalar_t__ outpkts; scalar_t__ inpkts; scalar_t__ conns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_read_estimator (struct ip_vs_kstats*,struct ip_vs_stats*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip_vs_copy_stats(struct ip_vs_kstats *dst, struct ip_vs_stats *src)
{
#define IP_VS_SHOW_STATS_COUNTER(c) dst->c = src->kstats.c - src->kstats0.c

	spin_lock_bh(&src->lock);

	IP_VS_SHOW_STATS_COUNTER(conns);
	IP_VS_SHOW_STATS_COUNTER(inpkts);
	IP_VS_SHOW_STATS_COUNTER(outpkts);
	IP_VS_SHOW_STATS_COUNTER(inbytes);
	IP_VS_SHOW_STATS_COUNTER(outbytes);

	ip_vs_read_estimator(dst, src);

	spin_unlock_bh(&src->lock);
}