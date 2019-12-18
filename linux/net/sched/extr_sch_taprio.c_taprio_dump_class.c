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
struct tcmsg {int /*<<< orphan*/  tcm_info; int /*<<< orphan*/  tcm_handle; int /*<<< orphan*/  tcm_parent; } ;
struct sk_buff {int dummy; } ;
struct netdev_queue {TYPE_1__* qdisc_sleeping; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_MIN (unsigned long) ; 
 int /*<<< orphan*/  TC_H_ROOT ; 
 struct netdev_queue* taprio_queue_get (struct Qdisc*,unsigned long) ; 

__attribute__((used)) static int taprio_dump_class(struct Qdisc *sch, unsigned long cl,
			     struct sk_buff *skb, struct tcmsg *tcm)
{
	struct netdev_queue *dev_queue = taprio_queue_get(sch, cl);

	tcm->tcm_parent = TC_H_ROOT;
	tcm->tcm_handle |= TC_H_MIN(cl);
	tcm->tcm_info = dev_queue->qdisc_sleeping->handle;

	return 0;
}