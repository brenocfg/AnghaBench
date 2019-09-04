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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct multiq_sched_data {int max_bands; int /*<<< orphan*/ ** queues; int /*<<< orphan*/  filter_list; int /*<<< orphan*/  block; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int num_tx_queues; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ ** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int multiq_tune (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int tcf_block_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct Qdisc*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int multiq_init(struct Qdisc *sch, struct nlattr *opt,
		       struct netlink_ext_ack *extack)
{
	struct multiq_sched_data *q = qdisc_priv(sch);
	int i, err;

	q->queues = NULL;

	if (!opt)
		return -EINVAL;

	err = tcf_block_get(&q->block, &q->filter_list, sch, extack);
	if (err)
		return err;

	q->max_bands = qdisc_dev(sch)->num_tx_queues;

	q->queues = kcalloc(q->max_bands, sizeof(struct Qdisc *), GFP_KERNEL);
	if (!q->queues)
		return -ENOBUFS;
	for (i = 0; i < q->max_bands; i++)
		q->queues[i] = &noop_qdisc;

	return multiq_tune(sch, opt, extack);
}