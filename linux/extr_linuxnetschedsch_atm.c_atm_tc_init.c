#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  classid; } ;
struct TYPE_4__ {int ref; TYPE_1__ common; int /*<<< orphan*/ * sock; int /*<<< orphan*/ * vcc; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  block; int /*<<< orphan*/ * q; int /*<<< orphan*/  list; } ;
struct atm_qdisc_data {int /*<<< orphan*/  task; TYPE_2__ link; int /*<<< orphan*/  flows; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_atm_dequeue ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int tcf_block_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int atm_tc_init(struct Qdisc *sch, struct nlattr *opt,
		       struct netlink_ext_ack *extack)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);
	int err;

	pr_debug("atm_tc_init(sch %p,[qdisc %p],opt %p)\n", sch, p, opt);
	INIT_LIST_HEAD(&p->flows);
	INIT_LIST_HEAD(&p->link.list);
	list_add(&p->link.list, &p->flows);
	p->link.q = qdisc_create_dflt(sch->dev_queue,
				      &pfifo_qdisc_ops, sch->handle, extack);
	if (!p->link.q)
		p->link.q = &noop_qdisc;
	pr_debug("atm_tc_init: link (%p) qdisc %p\n", &p->link, p->link.q);

	err = tcf_block_get(&p->link.block, &p->link.filter_list, sch,
			    extack);
	if (err)
		return err;

	p->link.vcc = NULL;
	p->link.sock = NULL;
	p->link.common.classid = sch->handle;
	p->link.ref = 1;
	tasklet_init(&p->task, sch_atm_dequeue, (unsigned long)sch);
	return 0;
}