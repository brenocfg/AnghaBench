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
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;
struct qfq_class {int /*<<< orphan*/  qdisc; TYPE_1__ common; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Qdisc* qdisc_replace (struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qfq_graft_class(struct Qdisc *sch, unsigned long arg,
			   struct Qdisc *new, struct Qdisc **old,
			   struct netlink_ext_ack *extack)
{
	struct qfq_class *cl = (struct qfq_class *)arg;

	if (new == NULL) {
		new = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
					cl->common.classid, NULL);
		if (new == NULL)
			new = &noop_qdisc;
	}

	*old = qdisc_replace(sch, new, &cl->qdisc);
	return 0;
}