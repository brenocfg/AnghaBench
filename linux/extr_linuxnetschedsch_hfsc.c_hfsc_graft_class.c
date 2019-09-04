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
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;
struct hfsc_class {scalar_t__ level; int /*<<< orphan*/  qdisc; TYPE_1__ cl_common; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Qdisc* qdisc_replace (struct Qdisc*,struct Qdisc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hfsc_graft_class(struct Qdisc *sch, unsigned long arg, struct Qdisc *new,
		 struct Qdisc **old, struct netlink_ext_ack *extack)
{
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	if (cl->level > 0)
		return -EINVAL;
	if (new == NULL) {
		new = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
					cl->cl_common.classid, NULL);
		if (new == NULL)
			new = &noop_qdisc;
	}

	*old = qdisc_replace(sch, new, &cl->qdisc);
	return 0;
}