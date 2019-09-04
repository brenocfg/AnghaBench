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
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 
 int dev_tx_weight ; 
 scalar_t__ need_resched () ; 
 scalar_t__ qdisc_restart (struct Qdisc*,int*) ; 

void __qdisc_run(struct Qdisc *q)
{
	int quota = dev_tx_weight;
	int packets;

	while (qdisc_restart(q, &packets)) {
		/*
		 * Ordered by possible occurrence: Postpone processing if
		 * 1. we've exceeded packet quota
		 * 2. another process needs the CPU;
		 */
		quota -= packets;
		if (quota <= 0 || need_resched()) {
			__netif_schedule(q);
			break;
		}
	}
}