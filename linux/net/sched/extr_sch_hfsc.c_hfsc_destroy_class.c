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
struct hfsc_class {int /*<<< orphan*/  rate_est; int /*<<< orphan*/  qdisc; int /*<<< orphan*/  block; } ;
struct hfsc_sched {struct hfsc_class root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hfsc_class*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hfsc_destroy_class(struct Qdisc *sch, struct hfsc_class *cl)
{
	struct hfsc_sched *q = qdisc_priv(sch);

	tcf_block_put(cl->block);
	qdisc_put(cl->qdisc);
	gen_kill_estimator(&cl->rate_est);
	if (cl != &q->root)
		kfree(cl);
}