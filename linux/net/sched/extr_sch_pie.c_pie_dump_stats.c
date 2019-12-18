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
struct tc_pie_xstats {int delay; int avg_dq_rate; int /*<<< orphan*/  ecn_mark; int /*<<< orphan*/  dropped; int /*<<< orphan*/  maxq; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  packets_in; int /*<<< orphan*/  prob; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecn_mark; int /*<<< orphan*/  dropped; int /*<<< orphan*/  maxq; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  packets_in; } ;
struct TYPE_4__ {int avg_dq_rate; int /*<<< orphan*/  qdelay; int /*<<< orphan*/  prob; } ;
struct pie_sched_data {TYPE_1__ stats; TYPE_2__ vars; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  st ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int PIE_SCALE ; 
 int /*<<< orphan*/  PSCHED_TICKS2NS (int /*<<< orphan*/ ) ; 
 int PSCHED_TICKS_PER_SEC ; 
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_pie_xstats*,int) ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int pie_dump_stats(struct Qdisc *sch, struct gnet_dump *d)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	struct tc_pie_xstats st = {
		.prob		= q->vars.prob,
		.delay		= ((u32)PSCHED_TICKS2NS(q->vars.qdelay)) /
				   NSEC_PER_USEC,
		/* unscale and return dq_rate in bytes per sec */
		.avg_dq_rate	= q->vars.avg_dq_rate *
				  (PSCHED_TICKS_PER_SEC) >> PIE_SCALE,
		.packets_in	= q->stats.packets_in,
		.overlimit	= q->stats.overlimit,
		.maxq		= q->stats.maxq,
		.dropped	= q->stats.dropped,
		.ecn_mark	= q->stats.ecn_mark,
	};

	return gnet_stats_copy_app(d, &st, sizeof(st));
}