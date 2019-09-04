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
struct tc_sfb_xstats {int /*<<< orphan*/  avgprob; int /*<<< orphan*/  maxprob; int /*<<< orphan*/  maxqlen; int /*<<< orphan*/  marked; int /*<<< orphan*/  childdrop; int /*<<< orphan*/  queuedrop; int /*<<< orphan*/  bucketdrop; int /*<<< orphan*/  penaltydrop; int /*<<< orphan*/  earlydrop; } ;
struct TYPE_2__ {int /*<<< orphan*/  marked; int /*<<< orphan*/  childdrop; int /*<<< orphan*/  queuedrop; int /*<<< orphan*/  bucketdrop; int /*<<< orphan*/  penaltydrop; int /*<<< orphan*/  earlydrop; } ;
struct sfb_sched_data {TYPE_1__ stats; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  st ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_sfb_xstats*,int) ; 
 struct sfb_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sfb_compute_qlen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sfb_sched_data*) ; 

__attribute__((used)) static int sfb_dump_stats(struct Qdisc *sch, struct gnet_dump *d)
{
	struct sfb_sched_data *q = qdisc_priv(sch);
	struct tc_sfb_xstats st = {
		.earlydrop = q->stats.earlydrop,
		.penaltydrop = q->stats.penaltydrop,
		.bucketdrop = q->stats.bucketdrop,
		.queuedrop = q->stats.queuedrop,
		.childdrop = q->stats.childdrop,
		.marked = q->stats.marked,
	};

	st.maxqlen = sfb_compute_qlen(&st.maxprob, &st.avgprob, q);

	return gnet_stats_copy_app(d, &st, sizeof(st));
}