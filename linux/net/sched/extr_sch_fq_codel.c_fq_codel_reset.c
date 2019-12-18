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
typedef  int /*<<< orphan*/  u32 ;
struct fq_codel_sched_data {int flows_cnt; scalar_t__ memory_usage; int /*<<< orphan*/  backlogs; struct fq_codel_flow* flows; int /*<<< orphan*/  old_flows; int /*<<< orphan*/  new_flows; } ;
struct fq_codel_flow {int /*<<< orphan*/  cvars; int /*<<< orphan*/  flowchain; } ;
struct TYPE_4__ {scalar_t__ backlog; } ;
struct TYPE_3__ {scalar_t__ qlen; } ;
struct Qdisc {TYPE_2__ qstats; TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codel_vars_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_codel_flow_purge (struct fq_codel_flow*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fq_codel_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void fq_codel_reset(struct Qdisc *sch)
{
	struct fq_codel_sched_data *q = qdisc_priv(sch);
	int i;

	INIT_LIST_HEAD(&q->new_flows);
	INIT_LIST_HEAD(&q->old_flows);
	for (i = 0; i < q->flows_cnt; i++) {
		struct fq_codel_flow *flow = q->flows + i;

		fq_codel_flow_purge(flow);
		INIT_LIST_HEAD(&flow->flowchain);
		codel_vars_init(&flow->cvars);
	}
	memset(q->backlogs, 0, q->flows_cnt * sizeof(u32));
	sch->q.qlen = 0;
	sch->qstats.backlog = 0;
	q->memory_usage = 0;
}