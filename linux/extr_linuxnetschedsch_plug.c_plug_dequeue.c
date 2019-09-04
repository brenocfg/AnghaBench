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
struct sk_buff {int dummy; } ;
struct plug_sched_data {int throttled; int /*<<< orphan*/  pkts_to_release; int /*<<< orphan*/  unplug_indefinite; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct sk_buff* qdisc_dequeue_head (struct Qdisc*) ; 
 struct plug_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *plug_dequeue(struct Qdisc *sch)
{
	struct plug_sched_data *q = qdisc_priv(sch);

	if (q->throttled)
		return NULL;

	if (!q->unplug_indefinite) {
		if (!q->pkts_to_release) {
			/* No more packets to dequeue. Block the queue
			 * and wait for the next release command.
			 */
			q->throttled = true;
			return NULL;
		}
		q->pkts_to_release--;
	}

	return qdisc_dequeue_head(sch);
}