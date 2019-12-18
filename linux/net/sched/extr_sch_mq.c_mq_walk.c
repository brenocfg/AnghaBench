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
struct qdisc_walker {int stop; unsigned int count; unsigned int skip; scalar_t__ (* fn ) (struct Qdisc*,unsigned int,struct qdisc_walker*) ;} ;
struct net_device {unsigned int num_tx_queues; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 scalar_t__ stub1 (struct Qdisc*,unsigned int,struct qdisc_walker*) ; 

__attribute__((used)) static void mq_walk(struct Qdisc *sch, struct qdisc_walker *arg)
{
	struct net_device *dev = qdisc_dev(sch);
	unsigned int ntx;

	if (arg->stop)
		return;

	arg->count = arg->skip;
	for (ntx = arg->skip; ntx < dev->num_tx_queues; ntx++) {
		if (arg->fn(sch, ntx + 1, arg) < 0) {
			arg->stop = 1;
			break;
		}
		arg->count++;
	}
}