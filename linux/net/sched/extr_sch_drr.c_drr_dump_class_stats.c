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
typedef  int /*<<< orphan*/  xstats ;
struct tc_drr_stats {int /*<<< orphan*/  deficit; } ;
struct gnet_dump {int dummy; } ;
struct drr_class {int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  deficit; struct Qdisc* qdisc; } ;
struct Qdisc {int /*<<< orphan*/  qstats; int /*<<< orphan*/  cpu_qstats; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_drr_stats*,int) ; 
 scalar_t__ gnet_stats_copy_basic (int /*<<< orphan*/ ,struct gnet_dump*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ gnet_stats_copy_rate_est (struct gnet_dump*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tc_drr_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qdisc_qlen_sum (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_running (struct Qdisc*) ; 

__attribute__((used)) static int drr_dump_class_stats(struct Qdisc *sch, unsigned long arg,
				struct gnet_dump *d)
{
	struct drr_class *cl = (struct drr_class *)arg;
	__u32 qlen = qdisc_qlen_sum(cl->qdisc);
	struct Qdisc *cl_q = cl->qdisc;
	struct tc_drr_stats xstats;

	memset(&xstats, 0, sizeof(xstats));
	if (qlen)
		xstats.deficit = cl->deficit;

	if (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, NULL, &cl->bstats) < 0 ||
	    gnet_stats_copy_rate_est(d, &cl->rate_est) < 0 ||
	    gnet_stats_copy_queue(d, cl_q->cpu_qstats, &cl_q->qstats, qlen) < 0)
		return -1;

	return gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}