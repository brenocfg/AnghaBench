#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xstats ;
struct tc_hfsc_stats {int /*<<< orphan*/  rtwork; int /*<<< orphan*/  work; int /*<<< orphan*/  period; int /*<<< orphan*/  level; } ;
struct TYPE_8__ {int /*<<< orphan*/  backlog; } ;
struct hfsc_class {TYPE_3__* qdisc; TYPE_4__ qstats; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  cl_cumul; int /*<<< orphan*/  cl_total; int /*<<< orphan*/  cl_vtperiod; int /*<<< orphan*/  level; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_5__ {int /*<<< orphan*/  backlog; } ;
struct TYPE_7__ {TYPE_2__ q; TYPE_1__ qstats; } ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_hfsc_stats*,int) ; 
 scalar_t__ gnet_stats_copy_basic (int /*<<< orphan*/ ,struct gnet_dump*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_running (struct Qdisc*) ; 

__attribute__((used)) static int
hfsc_dump_class_stats(struct Qdisc *sch, unsigned long arg,
	struct gnet_dump *d)
{
	struct hfsc_class *cl = (struct hfsc_class *)arg;
	struct tc_hfsc_stats xstats;

	cl->qstats.backlog = cl->qdisc->qstats.backlog;
	xstats.level   = cl->level;
	xstats.period  = cl->cl_vtperiod;
	xstats.work    = cl->cl_total;
	xstats.rtwork  = cl->cl_cumul;

	if (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch), d, NULL, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, NULL, &cl->qstats, cl->qdisc->q.qlen) < 0)
		return -1;

	return gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}