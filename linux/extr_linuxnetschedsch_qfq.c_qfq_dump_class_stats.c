#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xstats ;
struct tc_qfq_stats {int /*<<< orphan*/  lmax; int /*<<< orphan*/  weight; } ;
struct qfq_class {TYPE_3__* qdisc; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; TYPE_1__* agg; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_6__ {TYPE_2__ q; int /*<<< orphan*/  qstats; } ;
struct TYPE_4__ {int /*<<< orphan*/  lmax; int /*<<< orphan*/  class_weight; } ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_qfq_stats*,int) ; 
 scalar_t__ gnet_stats_copy_basic (int /*<<< orphan*/ ,struct gnet_dump*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tc_qfq_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_running (struct Qdisc*) ; 

__attribute__((used)) static int qfq_dump_class_stats(struct Qdisc *sch, unsigned long arg,
				struct gnet_dump *d)
{
	struct qfq_class *cl = (struct qfq_class *)arg;
	struct tc_qfq_stats xstats;

	memset(&xstats, 0, sizeof(xstats));

	xstats.weight = cl->agg->class_weight;
	xstats.lmax = cl->agg->lmax;

	if (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, NULL, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, NULL,
				  &cl->qdisc->qstats, cl->qdisc->q.qlen) < 0)
		return -1;

	return gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}