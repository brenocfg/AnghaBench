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
struct tc_hhf_xstats {int /*<<< orphan*/  hh_cur_count; int /*<<< orphan*/  hh_tot_count; int /*<<< orphan*/  hh_overlimit; int /*<<< orphan*/  drop_overlimit; } ;
struct hhf_sched_data {int /*<<< orphan*/  hh_flows_current_cnt; int /*<<< orphan*/  hh_flows_total_cnt; int /*<<< orphan*/  hh_flows_overlimit; int /*<<< orphan*/  drop_overlimit; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  st ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_hhf_xstats*,int) ; 
 struct hhf_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int hhf_dump_stats(struct Qdisc *sch, struct gnet_dump *d)
{
	struct hhf_sched_data *q = qdisc_priv(sch);
	struct tc_hhf_xstats st = {
		.drop_overlimit = q->drop_overlimit,
		.hh_overlimit	= q->hh_flows_overlimit,
		.hh_tot_count	= q->hh_flows_total_cnt,
		.hh_cur_count	= q->hh_flows_current_cnt,
	};

	return gnet_stats_copy_app(d, &st, sizeof(st));
}