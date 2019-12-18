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
typedef  int u16 ;
struct skbprio_sched_data {int highest_prio; int lowest_prio; int /*<<< orphan*/ * qdiscs; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 calc_new_high_prio(const struct skbprio_sched_data *q)
{
	int prio;

	for (prio = q->highest_prio - 1; prio >= q->lowest_prio; prio--) {
		if (!skb_queue_empty(&q->qdiscs[prio]))
			return prio;
	}

	/* SKB queue is empty, return 0 (default highest priority setting). */
	return 0;
}