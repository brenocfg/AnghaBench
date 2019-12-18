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
struct qfq_sched {int dummy; } ;
struct qfq_class {int /*<<< orphan*/  qdisc; int /*<<< orphan*/  rate_est; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qfq_class*) ; 
 struct qfq_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_rm_from_agg (struct qfq_sched*,struct qfq_class*) ; 

__attribute__((used)) static void qfq_destroy_class(struct Qdisc *sch, struct qfq_class *cl)
{
	struct qfq_sched *q = qdisc_priv(sch);

	qfq_rm_from_agg(q, cl);
	gen_kill_estimator(&cl->rate_est);
	qdisc_put(cl->qdisc);
	kfree(cl);
}