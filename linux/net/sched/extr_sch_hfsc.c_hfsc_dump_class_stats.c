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
typedef  int /*<<< orphan*/  xstats ;
struct tc_hfsc_stats {int /*<<< orphan*/  rtwork; int /*<<< orphan*/  work; int /*<<< orphan*/  period; int /*<<< orphan*/  level; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;
struct hfsc_class {TYPE_1__ qstats; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  cl_cumul; int /*<<< orphan*/  cl_total; int /*<<< orphan*/  cl_vtperiod; int /*<<< orphan*/  level; int /*<<< orphan*/  qdisc; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_hfsc_stats*,int) ; 
 scalar_t__ gnet_stats_copy_basic (int /*<<< orphan*/ ,struct gnet_dump*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_qstats_qlen_backlog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_running (struct Qdisc*) ; 

__attribute__((used)) static int
hfsc_dump_class_stats(struct Qdisc *sch, unsigned long arg,
	struct gnet_dump *d)
{
	struct hfsc_class *cl = (struct hfsc_class *)arg;
	struct tc_hfsc_stats xstats;
	__u32 qlen;

	qdisc_qstats_qlen_backlog(cl->qdisc, &qlen, &cl->qstats.backlog);
	xstats.level   = cl->level;
	xstats.period  = cl->cl_vtperiod;
	xstats.work    = cl->cl_total;
	xstats.rtwork  = cl->cl_cumul;

	if (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch), d, NULL, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, NULL, &cl->qstats, qlen) < 0)
		return -1;

	return gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}