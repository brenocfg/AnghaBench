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
struct netdev_queue {int dummy; } ;
struct Qdisc_ops {scalar_t__ (* init ) (struct Qdisc*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ;int /*<<< orphan*/  owner; } ;
struct Qdisc {unsigned int parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct Qdisc*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct Qdisc* qdisc_alloc (struct netdev_queue*,struct Qdisc_ops const*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 
 scalar_t__ stub1 (struct Qdisc*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct Qdisc *qdisc_create_dflt(struct netdev_queue *dev_queue,
				const struct Qdisc_ops *ops,
				unsigned int parentid,
				struct netlink_ext_ack *extack)
{
	struct Qdisc *sch;

	if (!try_module_get(ops->owner)) {
		NL_SET_ERR_MSG(extack, "Failed to increase module reference counter");
		return NULL;
	}

	sch = qdisc_alloc(dev_queue, ops, extack);
	if (IS_ERR(sch)) {
		module_put(ops->owner);
		return NULL;
	}
	sch->parent = parentid;

	if (!ops->init || ops->init(sch, NULL, extack) == 0)
		return sch;

	qdisc_put(sch);
	return NULL;
}