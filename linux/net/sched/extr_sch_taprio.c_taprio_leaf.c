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
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct netdev_queue* taprio_queue_get (struct Qdisc*,unsigned long) ; 

__attribute__((used)) static struct Qdisc *taprio_leaf(struct Qdisc *sch, unsigned long cl)
{
	struct netdev_queue *dev_queue = taprio_queue_get(sch, cl);

	if (!dev_queue)
		return NULL;

	return dev_queue->qdisc_sleeping;
}