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
struct netlink_ext_ack {int dummy; } ;
struct Qdisc_ops {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct Qdisc* ERR_PTR (int) ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int fifo_set_limit (struct Qdisc*,unsigned int) ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,struct Qdisc_ops*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 

struct Qdisc *fifo_create_dflt(struct Qdisc *sch, struct Qdisc_ops *ops,
			       unsigned int limit,
			       struct netlink_ext_ack *extack)
{
	struct Qdisc *q;
	int err = -ENOMEM;

	q = qdisc_create_dflt(sch->dev_queue, ops, TC_H_MAKE(sch->handle, 1),
			      extack);
	if (q) {
		err = fifo_set_limit(q, limit);
		if (err < 0) {
			qdisc_put(q);
			q = NULL;
		}
	}

	return q ? : ERR_PTR(err);
}